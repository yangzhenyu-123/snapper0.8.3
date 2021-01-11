/*
 * Copyright (c) [2011-2015] Novell, Inc.
 * Copyright (c) [2016-2019] SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#include "config.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include "snapper/Snapshot.h"
#include "snapper/Snapper.h"
#include "snapper/AppUtil.h"
#include "snapper/XmlFile.h"
#include "snapper/Filesystem.h"
#include "snapper/Btrfs.h"
#include "snapper/Enum.h"
#include "snapper/SnapperTmpl.h"
#include "snapper/SnapperDefines.h"
#include "snapper/Exception.h"
#include "snapper/Regex.h"
#include "snapper/Hooks.h"


namespace snapper
{
    using std::list;


    std::ostream& operator<<(std::ostream& s, const Snapshot& snapshot)
    {
		y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "()");
	s << "type:" << toString(snapshot.type) << " num:" << snapshot.num;

	if (snapshot.pre_num != 0)
	    s << " pre-num:" << snapshot.pre_num;

	s << " date:\"" << datetime(snapshot.date, true, true) << "\"";

	if (snapshot.uid != 0)
	    s << "uid:" << snapshot.uid;

	if (!snapshot.description.empty())
	    s << " description:\"" << snapshot.description << "\"";

	if (!snapshot.cleanup.empty())
	    s << " cleanup:\"" << snapshot.cleanup << "\"";

	if (!snapshot.userdata.empty())
	    s << " userdata:\"" << snapshot.userdata << "\"";

	return s;
    }


    Snapshot::Snapshot(const Snapper* snapper, SnapshotType type, unsigned int num, time_t date)
	: snapper(snapper), type(type), num(num), date(date), uid(0), pre_num(0),
	  mount_checked(false), mount_user_request(false), mount_use_count(0)
    {
    }


    Snapshot::~Snapshot()
    {
    }


    // Directory containing the actual content of the snapshot.
    // For btrfs e.g. "/" or "/home" for current and "/.snapshots/1/snapshot"
    // or "/home/.snapshots/1/snapshot" otherwise.
    // For ext4 e.g. "/" or "/home" for current and "/@1" or "/home@1"
    // otherwise.
    string
    Snapshot::snapshotDir() const
    {
		//y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	if (isCurrent())
	    return snapper->subvolumeDir();
	return snapper->getFilesystem()->snapshotDir(num);
	
    }


    SDir
    Snapshot::openInfoDir() const
    {
		//y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	if (isCurrent())
	    SN_THROW(IllegalSnapshotException());

	SDir infos_dir = snapper->openInfosDir();
	return SDir(infos_dir, decString(num));
	
    }


    SDir
    Snapshot::openSnapshotDir() const
    {
			//y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	if (isCurrent())
	    return snapper->openSubvolumeDir();
	return snapper->getFilesystem()->openSnapshotDir(num);
	
    }


    bool
    Snapshot::isReadOnly() const
    {
	y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	if (isCurrent())
	    return false;

	return snapper->getFilesystem()->isSnapshotReadOnly(num);
    }


    bool
    Snapshot::isDefault() const
    {
		y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ", default=" << snapper->getFilesystem()->isDefault(num) << ")");
	return snapper->getFilesystem()->isDefault(num);
	
    }


    void
    Snapshot::setDefault() const
    {
		y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	return snapper->getFilesystem()->setDefault(num);
    }


    bool
    Snapshot::isActive() const
    {
		y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "(" << getNum() << ")");
	return !isCurrent() && snapper->getFilesystem()->isActive(num);
    }


    uint64_t
    Snapshot::getUsedSpace() const
    {
		//y2err("now it is in  snapper/" << __FILE__  << " || now func is:" << __FUNCTION__ << "()");
#ifdef ENABLE_BTRFS_QUOTA

	const Btrfs* btrfs = dynamic_cast<const Btrfs*>(snapper->getFilesystem());
	if (!btrfs)
	    SN_THROW(QuotaException("quota only supported with btrfs"));

	SDir general_dir = btrfs->openGeneralDir();

	subvolid_t subvolid = get_id(openSnapshotDir().fd());
	qgroup_t qgroup = calc_qgroup(0, subvolid);

	QGroupUsage qgroup_usage = qgroup_query_usage(general_dir.fd(), qgroup);

	return qgroup_usage.exclusive;

#else

	SN_THROW(QuotaException("not implemented"));
	__builtin_unreachable();

#endif
    }


    void
    Snapshots::read()
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(开始运行)");
	Regex rx("^[0-9]+$");

	SDir infos_dir = snapper->openInfosDir();

	vector<string> infos = infos_dir.entries();
	for (vector<string>::const_iterator it1 = infos.begin(); it1 != infos.end(); ++it1)
	{
	    if (!rx.match(*it1))
		continue;

	    try
	    {
		SDir info_dir(infos_dir, *it1);
		int fd = info_dir.open("info.xml", O_NOFOLLOW | O_CLOEXEC);
		XmlFile file(fd, "");

		const xmlNode* root = file.getRootElement();
		const xmlNode* node = getChildNode(root, "snapshot");

		string tmp;

		SnapshotType type;
		if (!getChildValue(node, "type", tmp) || !toValue(tmp, type, true))
		{
		    y2err("type missing or invalid. not adding snapshot " << *it1);
		    continue;
		}

		unsigned int num;
		if (!getChildValue(node, "num", num) || num == 0)
		{
		    y2err("num missing or invalid. not adding snapshot " << *it1);
		    continue;
		}

		time_t date;
		if (!getChildValue(node, "date", tmp) || (date = scan_datetime(tmp, true)) == (time_t)(-1))
		{
		    y2err("date missing or invalid. not adding snapshot " << *it1);
		    continue;
		}

		Snapshot snapshot(snapper, type, num, date);

		*it1 >> num;
		if (num != snapshot.num)
		{
		    y2err("num mismatch. not adding snapshot " << *it1);
		    continue;
		}

		getChildValue(node, "uid", snapshot.uid);

		getChildValue(node, "pre_num", snapshot.pre_num);

		getChildValue(node, "description", snapshot.description);

		getChildValue(node, "cleanup", snapshot.cleanup);

		const list<const xmlNode*> l = getChildNodes(node, "userdata");
		for (list<const xmlNode*>::const_iterator it2 = l.begin(); it2 != l.end(); ++it2)
		{
		    string key, value;
		    getChildValue(*it2, "key", key);
		    getChildValue(*it2, "value", value);
		    if (!key.empty())
			snapshot.userdata[key] = value;
		}

		if (!snapper->getFilesystem()->checkSnapshot(snapshot.num))
		{
		    y2err("snapshot check failed. not adding snapshot " << *it1);
		    continue;
		}

		entries.push_back(snapshot);
	    }
	    catch (const IOErrorException& e)
	    {
		y2err("loading " << *it1 << " failed");
	    }
	}

	entries.sort();
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(结束运行)");
	y2mil("found " << entries.size() << " snapshots");
    }


    void
    Snapshots::check() const
    {
		//y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "()" );
	time_t t0 = time(NULL);
	time_t t1 = (time_t)(-1);

	for (const_iterator i1 = begin(); i1 != end(); ++i1)
	{
	    switch (i1->type)
	    {
		case SINGLE:
		{
		}
		break;

		case PRE:
		{
		    int n = 0;
		    for (const_iterator i2 = begin(); i2 != end(); ++i2)
			if (i2->pre_num == i1->num)
			    n++;
		    if (n > 1)
			y2err("pre-num " << i1->num << " has " << n << " post-nums");
		}
		break;

		case POST:
		{
		    if (i1->pre_num > i1->num)
			y2err("pre-num " << i1->pre_num << " larger than post-num " << i1->num);

		    const_iterator i2 = find(i1->pre_num);
		    if (i2 == end())
			y2err("pre-num " << i1->pre_num << " for post-num " << i1->num <<
			      " does not exist");
		    else
			if (i2->type != PRE)
			    y2err("pre-num " << i1->pre_num << " for post-num " << i1->num <<
				  " is of type " << toString(i2->type));
		}
		break;
	    }

	    if (!i1->isCurrent())
	    {
		if (i1->date > t0)
		    y2err("snapshot num " << i1->num << " in future");

		if (t1 != (time_t)(-1) && i1->date < t1)
		    y2err("time shift detected at snapshot num " << i1->num);

		t1 = i1->date;
	    }
	}
    }


    void
    Snapshots::checkUserdata(const map<string, string>& userdata) const
    {
		//y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "()");
	for (map<string, string>::const_iterator it = userdata.begin(); it != userdata.end(); ++it)
	{
	    if (it->first.empty() || it->first.find_first_of(",=") != string::npos) //map中元素左值
		SN_THROW(InvalidUserdataException());

	    if (it->second.find_first_of(",=") != string::npos)//map中元素右值
		SN_THROW(InvalidUserdataException());
	}
    }


    void
    Snapshots::initialize()
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(开始)");
	entries.clear();

	Snapshot snapshot(snapper, SINGLE, 0, (time_t)(-1));
	snapshot.description = "current";
	entries.push_back(snapshot);
	try
	{
	    read();
	}
	catch (const IOErrorException& e)
	{
	    y2err("reading failed");
	}
	
	check();
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(结束)");
    }


    Snapshots::iterator
    Snapshots::findPost(const_iterator pre)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(pre=" << pre->getNum() << ")");
	if (pre == entries.end() || pre->isCurrent() || pre->getType() != PRE)
	    SN_THROW(IllegalSnapshotException());

	for (iterator it = begin(); it != end(); ++it)
	{
	    if (it->getType() == POST && it->getPreNum() == pre->getNum())
		return it;
	}

	return end();
    }


    Snapshots::const_iterator
    Snapshots::findPost(const_iterator pre) const
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__  << "(const pre=" << pre->getNum() << ")");
	if (pre == entries.end() || pre->isCurrent() || pre->getType() != PRE)
	    SN_THROW(IllegalSnapshotException());

	for (const_iterator it = begin(); it != end(); ++it)
	{
	    if (it->getType() == POST && it->getPreNum() == pre->getNum())
		return it;
	}

	return end();
    }


    Snapshots::iterator
    Snapshots::findPre(const_iterator post)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(post)" );
	if (post == entries.end() || post->isCurrent() || post->getType() != POST)
	    SN_THROW(IllegalSnapshotException());

	return find(post->pre_num);
    }


    Snapshots::const_iterator
    Snapshots::findPre(const_iterator post) const
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(const post)" );
	if (post == entries.end() || post->isCurrent() || post->getType() != POST)
	    SN_THROW(IllegalSnapshotException());

	return find(post->pre_num);
    }


    unsigned int
    Snapshots::nextNumber()
    {
		
	unsigned int num = entries.empty() ? 0 : entries.rbegin()->num;
	//y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(" << num << ")");
	SDir infos_dir = snapper->openInfosDir();

	while (true)
	{
	    ++num;

	    if (snapper->getFilesystem()->checkSnapshot(num))
		continue;

	    if (infos_dir.mkdir(decString(num), 0777) == 0)
		break;

	    if (errno == EEXIST)
		continue;

	    SN_THROW(IOErrorException(sformat("mkdir failed errno:%d (%s)", errno,
					      stringerror(errno).c_str())));
	}

	infos_dir.chmod(decString(num), 0755, 0);

	return num;
    }


    void
    Snapshot::writeInfo() const
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(开始)");
	XmlFile xml;
	xmlNode* node = xmlNewNode("snapshot");
	xml.setRootElement(node);

	setChildValue(node, "type", toString(type));

	setChildValue(node, "num", num);

	setChildValue(node, "date", datetime(date, true, true));

	if (uid != 0)
	    setChildValue(node, "uid", uid);

	if (type == POST)
	    setChildValue(node, "pre_num", pre_num);

	if (!description.empty())
	    setChildValue(node, "description", description);

	if (!cleanup.empty())
	    setChildValue(node, "cleanup", cleanup);

	for (map<string, string>::const_iterator it = userdata.begin(); it != userdata.end(); ++it)
	{
	    xmlNode* userdata_node = xmlNewChild(node, "userdata");
	    setChildValue(userdata_node, "key", it->first);
	    setChildValue(userdata_node, "value", it->second);
	}

	string file_name = "info.xml";
	string tmp_name = file_name + ".tmp-XXXXXX";

	SDir info_dir = openInfoDir();

	xml.save(info_dir.mktemp(tmp_name));

	if (info_dir.rename(tmp_name, file_name) != 0)
	    SN_THROW(IOErrorException(sformat("rename info.xml failed infoDir:%s errno:%d (%s)",
					      info_dir.fullname().c_str(), errno,
					      stringerror(errno).c_str())));
	
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(结束)");
    }


    void
    Snapshot::mountFilesystemSnapshot(bool user_request) const
    {
	y2err("now it is in  snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(user_request=" << user_request << ")");
	if (isCurrent())
	    SN_THROW(IllegalSnapshotException());

	if (!mount_checked)
	{
	    mount_user_request = snapper->getFilesystem()->isSnapshotMounted(num);
	    mount_checked = true;
	}

	if (user_request)
	    mount_user_request = true;
	else
	    mount_use_count++;

	snapper->getFilesystem()->mountSnapshot(num);
    }


    void
    Snapshot::umountFilesystemSnapshot(bool user_request) const
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(user_request=" << user_request << ")");
	if (isCurrent())
	    SN_THROW(IllegalSnapshotException());

	if (!mount_checked)
	{
	    mount_user_request = snapper->getFilesystem()->isSnapshotMounted(num);
	    mount_checked = true;
	}

	if (user_request)
	    mount_user_request = false;
	else
	    mount_use_count--;

	if (user_request && mount_use_count == 0)
	    snapper->getFilesystem()->umountSnapshot(num);
    }


    void
    Snapshot::handleUmountFilesystemSnapshot() const
    {
		
	if (!mount_checked)
	{
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(mount_check=" << mount_checked << ", num=" << num << ")");
		return;
	}
	    

	if (!mount_user_request && mount_use_count == 0)
	{
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(mount_user_request=" << mount_user_request << ", mount_use_count=" << mount_use_count << ", mount_checked=" << mount_checked << ", num=" << num << ")");
		snapper->getFilesystem()->umountSnapshot(num);
	}
	    
    }


    void
    Snapshot::createFilesystemSnapshot(unsigned int num_parent, bool read_only, bool empty) const
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(num_parent=" \
	<< num_parent << ", num=" << num << ",read_only=" << read_only <<",empty=" << empty << ") （开始）");
	if (isCurrent())
	    SN_THROW(IllegalSnapshotException());

	snapper->getFilesystem()->createSnapshot(num, num_parent, read_only, !cleanup.empty(),
						 empty);
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(num_parent=" \
	<< num_parent << ", num=" << num << ",read_only=" << read_only <<",empty=" << empty << ") （结束）");
    }


    void
    Snapshot::createFilesystemSnapshotOfDefault(bool read_only) const
    {
	y2err("now it is in snapper/" << __FILE__ <<  " || func name is:" << __FUNCTION__ << "(read_only=" << read_only << ", num=" << num << ") （开始）");
	if (isCurrent())
	    SN_THROW(IllegalSnapshotException());
	
	snapper->getFilesystem()->createSnapshotOfDefault(num, read_only, !cleanup.empty());
	y2err("now it is in snapper/" << __FILE__ <<  " || func name is:" << __FUNCTION__ << "(read_only=" << read_only << ", num=" << num << ") （结束）");
    }


    void
    Snapshot::deleteFilesystemSnapshot() const
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(num=" << num << ") (开始) ");
	snapper->getFilesystem()->umountSnapshot(num);
	snapper->getFilesystem()->deleteSnapshot(num);
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(num=" << num << ") (结束) ");
    }


    Snapshots::iterator
    Snapshots::createSingleSnapshot(const SCD& scd)
    {
	checkUserdata(scd.userdata);
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(scd.uid=" << scd.uid << ")");
	Snapshot snapshot(snapper, SINGLE, nextNumber(), time(NULL));
	snapshot.uid = scd.uid;
	snapshot.description = scd.description;
	snapshot.cleanup = scd.cleanup;
	snapshot.userdata = scd.userdata;
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(scd.uid=" << scd.uid << ")" << " (结束 返回createHelper)" );
	return createHelper(snapshot, getSnapshotCurrent(), scd.read_only, scd.empty);
    }


    Snapshots::iterator
    Snapshots::createSingleSnapshot(const_iterator parent, const SCD& scd)
    {
	checkUserdata(scd.userdata);
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(parent_num=" << parent->getNum() << ", scd.uid=" << scd.uid << ")");
	Snapshot snapshot(snapper, SINGLE, nextNumber(), time(NULL));
	snapshot.uid = scd.uid;
	snapshot.description = scd.description;
	snapshot.cleanup = scd.cleanup;
	snapshot.userdata = scd.userdata;

	return createHelper(snapshot, parent, scd.read_only);
    }


    Snapshots::iterator
    Snapshots::createSingleSnapshotOfDefault(const SCD& scd)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(scd.uid=" << scd.uid  << ")");
	checkUserdata(scd.userdata);

	Snapshot snapshot(snapper, SINGLE, nextNumber(), time(NULL));
	snapshot.uid = scd.uid;
	snapshot.description = scd.description;
	snapshot.cleanup = scd.cleanup;
	snapshot.userdata = scd.userdata;

	return createHelper(snapshot, end(), scd.read_only);
    }


    Snapshots::iterator
    Snapshots::createPreSnapshot(const SCD& scd)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(scd.uid=" << scd.uid << ")" << " (开始)");
	checkUserdata(scd.userdata);
	Snapshot snapshot(snapper, PRE, nextNumber(), time(NULL));
	snapshot.uid = scd.uid;
	snapshot.description = scd.description;
	snapshot.cleanup = scd.cleanup;
	snapshot.userdata = scd.userdata;
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(scd.uid=" << scd.uid << ")" << " (结束 返回createHelper)");
	return createHelper(snapshot, getSnapshotCurrent(), scd.read_only);
    }


    Snapshots::iterator
    Snapshots::createPostSnapshot(Snapshots::const_iterator pre, const SCD& scd)
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(pre_num=" << pre->getNum() << ", scd.uid=" << scd.uid << ") （开始）");
	if (pre == entries.end() || pre->isCurrent() || pre->getType() != PRE ||
	    findPost(pre) != entries.end())
	    SN_THROW(IllegalSnapshotException());

	checkUserdata(scd.userdata);
	
	Snapshot snapshot(snapper, POST, nextNumber(), time(NULL));
	snapshot.pre_num = pre->getNum();
	snapshot.uid = scd.uid;
	snapshot.description = scd.description;
	snapshot.cleanup = scd.cleanup;
	snapshot.userdata = scd.userdata;
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(pre_num=" << pre->getNum() << ", scd.uid=" << scd.uid << ") （结束返回createHelper）");
	return createHelper(snapshot, getSnapshotCurrent(), scd.read_only);
    }


    Snapshots::iterator
    Snapshots::createHelper(Snapshot& snapshot, const_iterator parent, bool read_only,
			    bool empty)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(dir=" << snapshot.snapshotDir() << ", parent=" << parent->getNum() <<", read_only=" << read_only << ", empty=" << empty <<") (开始)");
	// parent == end indicates the btrfs default subvolume. Unclean, but
	// adding a special snapshot like current needs too many API changes.

	try
	{
	    if (parent != end())
		snapshot.createFilesystemSnapshot(parent->getNum(), read_only, empty);
	    else
		snapshot.createFilesystemSnapshotOfDefault(read_only);
	}
	catch (const CreateSnapshotFailedException& e)
	{
	    SN_CAUGHT(e);

	    SDir infos_dir = snapper->openInfosDir();
	    infos_dir.unlink(decString(snapshot.getNum()), AT_REMOVEDIR);

	    SN_RETHROW(e);
	}

	try
	{
	    snapshot.writeInfo();
	}
	catch (const IOErrorException& e)
	{
	    SN_CAUGHT(e);

	    snapshot.deleteFilesystemSnapshot();
	    SDir infos_dir = snapper->openInfosDir();
	    infos_dir.unlink(decString(snapshot.getNum()), AT_REMOVEDIR);

	    SN_RETHROW(e);
	}

	Hooks::create_snapshot(snapper->subvolumeDir(), snapper->getFilesystem());
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(dir=" << snapshot.snapshotDir() << ", parent=" << parent->getNum() <<", read_only=" << read_only << ", empty=" << empty <<") (结束)");
	return entries.insert(entries.end(), snapshot);
    }


    static bool
    is_filelist_file(unsigned char type, const char* name)
    {
	return (type == DT_UNKNOWN || type == DT_REG) && (fnmatch("filelist-*.txt", name, 0) == 0);
    }


    void
    Snapshots::modifySnapshot(iterator snapshot, const SMD& smd)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(iterator snapshot, const SMD& smd)");
	if (snapshot == entries.end() || snapshot->isCurrent())
	    SN_THROW(IllegalSnapshotException());

	checkUserdata(smd.userdata);

	snapshot->description = smd.description;
	snapshot->cleanup = smd.cleanup;
	snapshot->userdata = smd.userdata;

	snapshot->writeInfo();

	Hooks::modify_snapshot(snapper->subvolumeDir(), snapper->getFilesystem());
    }


    void
    Snapshots::deleteSnapshot(iterator snapshot)
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(snapshot.num=" << snapshot->getNum() <<")");
	if (snapshot == entries.end() || snapshot->isCurrent() || snapshot->isDefault() ||
	    snapshot->isActive())
	    SN_THROW(IllegalSnapshotException());

	snapshot->deleteFilesystemSnapshot();

	SDir info_dir = snapshot->openInfoDir();

	info_dir.unlink("info.xml", 0);

	vector<string> tmp1 = info_dir.entries(is_filelist_file);
	for (vector<string>::const_iterator it = tmp1.begin(); it != tmp1.end(); ++it)
	{
	    info_dir.unlink(*it, 0);
	}

	for (Snapshots::iterator it = begin(); it != end(); ++it)
	{
	    if (!it->isCurrent())
	    {
		SDir tmp2 = it->openInfoDir();
		tmp2.unlink("filelist-" + decString(snapshot->getNum()) + ".txt", 0);
	    }
	}

	SDir infos_dir = snapper->openInfosDir();
	infos_dir.unlink(decString(snapshot->getNum()), AT_REMOVEDIR);

	entries.erase(snapshot);

	Hooks::delete_snapshot(snapper->subvolumeDir(), snapper->getFilesystem());
	y2err("now it is in snapper/" <<  __FILE__ << " | func name: " << __FUNCTION__ << "(end)");
    }


    Snapshots::iterator
    Snapshots::getDefault()
    {
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(filesystem.getdefault)" );
	std::pair<bool, unsigned int> tmp = snapper->getFilesystem()->getDefault();

	return tmp.first ? find(tmp.second) : end();
    }


    Snapshots::const_iterator
    Snapshots::getDefault() const
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(const)" );
	std::pair<bool, unsigned int> tmp = snapper->getFilesystem()->getDefault();

	return tmp.first ? find(tmp.second) : end();
    }


    Snapshots::const_iterator
    Snapshots::getActive() const
    {
	
	std::pair<bool, unsigned int> tmp = snapper->getFilesystem()->getActive();
	y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(tmp.first=" << tmp.first << ", tmp.second=" << tmp.second << ")" );
	return tmp.first ? find(tmp.second) : end();
    }


    struct num_is
    {
	num_is(unsigned int num) : num(num) {}
	bool operator()(const Snapshot& s) const { return s.getNum() == num; }
	const unsigned int num;
    };


    Snapshots::iterator
    Snapshots::find(unsigned int num)
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is:" << __FUNCTION__ << "(num=" << num << ")" );
	return find_if(entries.begin(), entries.end(), num_is(num));
    }


    Snapshots::const_iterator
    Snapshots::find(unsigned int num) const
    {
		y2err("now it is in snapper/" << __FILE__  << " || func name is: const " << __FUNCTION__ << "(num=" << num << ")" );
	return find_if(entries.begin(), entries.end(), num_is(num));
    }

}
