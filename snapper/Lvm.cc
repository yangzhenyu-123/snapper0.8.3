/*
 * Copyright (c) [2011-2014] Novell, Inc.
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

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <boost/algorithm/string.hpp>

#include "snapper/Log.h"
#include "snapper/Filesystem.h"
#include "snapper/Lvm.h"
#include "snapper/Snapper.h"
#include "snapper/SnapperTmpl.h"
#include "snapper/SystemCmd.h"
#include "snapper/SnapperDefines.h"
#include "snapper/Regex.h"
#include "snapper/LvmCache.h"
#ifdef ENABLE_SELINUX
#include "snapper/Selinux.h"
#endif


namespace snapper
{

    Filesystem*
    Lvm::create(const string& fstype, const string& subvolume, const string& root_prefix)
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
	<< "(" << fstype << ", " << subvolume << ", " << root_prefix << ") （开始）" );
	Regex rx("^lvm\\(([_a-z0-9]+)\\)$");
	if (rx.match(fstype))
	{
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
	<< "(" << fstype << ", " << subvolume << ", " << root_prefix << ") （结束 返回Lvm ）" );
		return new Lvm(subvolume, root_prefix, rx.cap(1));
	}
	return NULL;
    }


    Lvm::Lvm(const string& subvolume, const string& root_prefix, const string& mount_type)
	: Filesystem(subvolume, root_prefix), mount_type(mount_type),
	  caps(LvmCapabilities::get_lvm_capabilities()),
	  cache(LvmCache::get_lvm_cache()), sh(NULL)
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
		<< "(" << subvolume << ", " << root_prefix << ", " << mount_type << ") （开始)" );
	if (access(LVCREATEBIN, X_OK) != 0)
	{
	    throw ProgramNotInstalledException(LVCREATEBIN " not installed");
	}

	if (access(LVSBIN, X_OK) != 0)
	{
	    throw ProgramNotInstalledException(LVSBIN " not installed");
	}

	if (access(LVCHANGEBIN, X_OK) != 0)
	{
	    throw ProgramNotInstalledException(LVCHANGEBIN " not installed");
	}

	bool found = false;
	MtabData mtab_data;

	if (!getMtabData(subvolume, found, mtab_data))
	    throw InvalidConfigException();

	if (!found)
	{
	    y2err("filesystem not mounted");
	    throw InvalidConfigException();
	}

	if (!detectThinVolumeNames(mtab_data))
	    throw InvalidConfigException();

	mount_options = filter_mount_options(mtab_data.options);
	if (mount_type == "xfs")
	{
	    mount_options.push_back("nouuid");
	    mount_options.push_back("norecovery");
	}

#ifdef ENABLE_SELINUX
	try
	{
	    sh = SelinuxLabelHandle::get_selinux_handle();
	}
	catch (const SelinuxException& e)
	{
	    SN_RETHROW(e);
	}
#endif
			y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
		<< "(" << subvolume << ", " << root_prefix << ", " << mount_type << ") （结束)" );
    }


    void
    Lvm::createLvmConfig(const SDir& subvolume_dir, int mode) const
    {
	int r1 = subvolume_dir.mkdir(".snapshots", mode);
	if (r1 != 0 && errno != EEXIST)
	{
	    y2err("mkdir failed errno:" << errno << " (" << strerror(errno) << ")");
	    SN_THROW(CreateConfigFailedException("mkdir failed"));
	}
	 y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(subvolume_dir=" << subvolume_dir.fullname() << ", mode=," << mode << ");");
    }


    void
    Lvm::createConfig() const
    {
	int mode = 0750;
	SDir subvolume_dir = openSubvolumeDir();

#ifdef ENABLE_SELINUX
	if (_is_selinux_enabled())
	{
	    assert(sh);

	    char* con = NULL;

	    try
	    {
		string path(subvolume_dir.fullname() + "/.snapshots");

		con = sh->selabel_lookup(path, mode);
		if (con)
		{
		    // race free mkdir with correct Selinux context preset
		    DefaultSelinuxFileContext defcon(con);
		    createLvmConfig(subvolume_dir, mode);
		}
		else
		{
		    y2deb("Selinux policy does not define context for path: " << path);

		    // race free mkdir with correct Selinux context preset even in case
		    // Selinux policy does not define context for the path
		    SnapperContexts scontexts;
		    DefaultSelinuxFileContext defcon(scontexts.subvolume_context());

		    createLvmConfig(subvolume_dir, mode);
		}

		freecon(con);

		return;
	    }
	    catch (const SelinuxException& e)
	    {
		SN_CAUGHT(e);
		freecon(con);
		// fall through intentional
	    }
	    catch (const CreateConfigFailedException& e)
	    {
		freecon(con);
		SN_RETHROW(e);
	    }
	}
#endif
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(dir=" 
	<< subvolume_dir.fullname() << ", mode=" << mode << ") （开始)");	
	createLvmConfig(subvolume_dir, mode);
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(dir=" 
	<< subvolume_dir.fullname() << ", mode=" << mode << ") （结束)");	
    }


    void
    Lvm::deleteConfig() const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "()");
	SDir subvolume_dir = openSubvolumeDir();

	int r1 = subvolume_dir.unlink(".snapshots", AT_REMOVEDIR);
	if (r1 != 0)
	{
	    y2err("rmdir failed errno:" << errno << " (" << strerror(errno) << ")");
	    throw DeleteConfigFailedException("rmdir failed");
	}
    }


    string
    Lvm::snapshotDir(unsigned int num) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(num=" << num << ")");
	return (subvolume == "/" ? "" : subvolume) + "/.snapshots/" + decString(num) +
	    "/snapshot";
    }


    SDir
    Lvm::openInfosDir() const
    {
	SDir subvolume_dir = openSubvolumeDir();
	SDir infos_dir(subvolume_dir, ".snapshots");

	struct stat stat;
	if (infos_dir.stat(&stat) != 0)
	{
	    throw IOErrorException("stat on .snapshots failed");
	}

	if (stat.st_uid != 0)
	{
	    y2err(".snapshots must have owner root");
	    throw IOErrorException(".snapshots must have owner root");
	}

	if (stat.st_gid != 0 && stat.st_mode & S_IWGRP)
	{
	    y2err(".snapshots must have group root or must not be group-writable");
	    throw IOErrorException(".snapshots must have group root or must not be group-writable");
	}

	if (stat.st_mode & S_IWOTH)
	{
	    y2err(".snapshots must not be world-writable");
	    throw IOErrorException(".snapshots must not be world-writable");
	}
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(dir=" << infos_dir.fullname() << ")" );
	return infos_dir;
    }


    SDir
    Lvm::openSnapshotDir(unsigned int num) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(num=" << num << ")");
	SDir info_dir = openInfoDir(num);
	SDir snapshot_dir(info_dir, "snapshot");

	return snapshot_dir;
    }


    string
    Lvm::snapshotLvName(unsigned int num) const
    {
	y2err("snapper/Lvm::" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" << num << ")");
	return lv_name + "-snapshot" + decString(num);
    }


    void
    Lvm::createSnapshot(unsigned int num, unsigned int num_parent, bool read_only, bool quota,
			bool empty) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" 
		 << num << ",num_parent=" << num_parent << ",read_only=" << read_only << ",quata=" << quota << ",empty=" << empty << ") （开始)");
	if (num_parent != 0 || !read_only)
	    throw std::logic_error("not implemented");

	SDir info_dir = openInfoDir(num);
	int r1 = info_dir.mkdir("snapshot", 0755);
	if (r1 != 0 && errno != EEXIST)
	{
	    y2err("mkdir failed errno:" << errno << " (" << strerror(errno) << ")");
	    throw CreateSnapshotFailedException();
	}

	try
	{
	    cache->create_snapshot(vg_name, lv_name, snapshotLvName(num));
	}
	catch (const LvmCacheException& e)
	{
	    y2deb(cache);
	    throw CreateSnapshotFailedException();
	}
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" 
		 << num << ",num_parent=" << num_parent << ",read_only=" << read_only << ",quata=" << quota << ",empty=" << empty << ") （结束)");
    }


    void
    Lvm::deleteSnapshot(unsigned int num) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" << num << ") （begin)");
	try
	{
	    cache->delete_snapshot(vg_name, snapshotLvName(num));
	}
	catch (const LvmCacheException& e)
	{
	    y2deb(cache);
	    throw DeleteSnapshotFailedException();
	}

	SDir info_dir = openInfoDir(num);
	info_dir.unlink("snapshot", AT_REMOVEDIR);

	SDir infos_dir = openInfosDir();
	infos_dir.unlink(decString(num), AT_REMOVEDIR);

	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" << num << ") (end)");
    }


    bool
    Lvm::isSnapshotMounted(unsigned int num) const
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" << num << ")");
	bool mounted = false;
	MtabData mtab_data;

	if (!getMtabData(snapshotDir(num), mounted, mtab_data))
	    throw IsSnapshotMountedFailedException();
	return mounted;
    }


    void
    Lvm::mountSnapshot(unsigned int num) const
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(num=" << num << ") " << "挂载快照卷" << num);
	boost::unique_lock<boost::mutex> lock(mount_mutex);

	if (isSnapshotMounted(num))
	    return;
	y2err("第一步激活快照卷");
	try
	{
	    activateSnapshot(vg_name, snapshotLvName(num));
	}
	catch (const LvmActivationException& e)
	{
	    throw MountSnapshotFailedException();
	}
	y2err("成功激活快照卷");
	y2err("第二步挂载快照卷");
	SDir snapshot_dir = openSnapshotDir(num);

	if (!mount(getDevice(num), snapshot_dir, mount_type, mount_options))
	    throw MountSnapshotFailedException();

	y2err("挂载快照卷成功");
    }


    void
    Lvm::umountSnapshot(unsigned int num) const
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(snapshot_num=" << num << ")");
	boost::unique_lock<boost::mutex> lock(mount_mutex);

	if (isSnapshotMounted(num))
	{
	    SDir info_dir = openInfoDir(num);

	    if (!umount(info_dir, "snapshot"))
		throw UmountSnapshotFailedException();

	}

	try
	{
	    deactivateSnapshot(vg_name, snapshotLvName(num));
	}
	catch (const LvmDeactivatationException& e)
	{
	    y2war("Couldn't deactivate: " << vg_name << "/" << lv_name);
	}
    }


    bool
    Lvm::isSnapshotReadOnly(unsigned int num) const
    {
	// TODO

	return true;
    }


    bool
    Lvm::checkSnapshot(unsigned int num) const
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(num=" << num << ")" << " || return detectInactiveSnapshot()");
	return detectInactiveSnapshot(vg_name, snapshotLvName(num));
    }


    bool
    Lvm::detectThinVolumeNames(const MtabData& mtab_data)
    {
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
	 << "(" << mtab_data.device << ", " << mtab_data.type << ", " << mtab_data.dir << ") (开始)");
	Regex rx("^/dev/mapper/(.+[^-])-([^-].+)$");
	if (!rx.match(mtab_data.device))
	{
	    y2err("could not detect lvm names from '" << mtab_data.device << "'");
	    return false;
	}

	vg_name = boost::replace_all_copy(rx.cap(1), "--", "-");
	lv_name = boost::replace_all_copy(rx.cap(2), "--", "-");

	try
	{
	    cache->add_or_update(vg_name, lv_name);
	}
	catch (const LvmCacheException& e)
	{
	    y2deb(cache);
	    return false;
	}
	y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ 
	 << "(" << mtab_data.device << ", " << mtab_data.type << ", " << mtab_data.dir << ") (结束 返回contains_thin)");
	
	return cache->contains_thin(vg_name, lv_name);
    }


    string
    Lvm::getDevice(unsigned int num) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__ << "(num=" << num << ")");
	return "/dev/mapper/" + boost::replace_all_copy(vg_name, "-", "--") + "-" +
	    boost::replace_all_copy(snapshotLvName(num), "-", "--");
    }


    void
    Lvm::activateSnapshot(const string& vg_name, const string& lv_name) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(" << vg_name <<", "<< lv_name << ")");
	try
	{
	    cache->activate(vg_name, lv_name);
	}
	catch (const LvmCacheException& e)
	{
	    y2deb(cache);
	    throw LvmActivationException();
	}
    }


    void
    Lvm::deactivateSnapshot(const string& vg_name, const string& lv_name) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(" << vg_name <<", "<< lv_name << ")");
	try
	{
	    cache->deactivate(vg_name, lv_name);
	}
	catch (const LvmCacheException& e)
	{
	    y2deb(cache);
	    throw LvmDeactivatationException();
	}
    }


    bool
    Lvm::detectInactiveSnapshot(const string& vg_name, const string& lv_name) const
    {
		y2err("snapper/" << __FILE__ << "|| now func is:" << __FUNCTION__  << "(" << vg_name <<", "<< lv_name << ")" << " || return contains(vg,lv)");
	return cache->contains(vg_name, lv_name);
    }


    LvmCapabilities::LvmCapabilities()
	: ignoreactivationskip(), time_support(false)
    {
	SystemCmd cmd(string(LVMBIN " version"));

	if (cmd.retcode() != 0 || cmd.stdout().empty())
	{
	    y2war("Couldn't get LVM version info");
	}
	else
	{
	    Regex rx(".*LVM[[:space:]]+version:[[:space:]]+([0-9]+)\\.([0-9]+)\\.([0-9]+).*$");

	    if (!rx.match(cmd.stdout().front()))
	    {
		y2war("LVM version format didn't match");
	    }
	    else
	    {
		uint16_t maj, min, rev;

		rx.cap(1) >> maj;
		rx.cap(2) >> min;
		rx.cap(3) >> rev;

		lvm_version version(maj, min, rev);

		if (version >= lvm_version(2,2,99))
		{
		    ignoreactivationskip = " -K";
		}

		time_support = (version >= lvm_version(2,2,88));
	    }
	}
    }


    bool
    operator>=(const lvm_version& a, const lvm_version& b)
    {
	return a.version >= b.version;
    }


    LvmCapabilities*
    LvmCapabilities::get_lvm_capabilities()
    {
	/*
	 * NOTE: verify only one thread can access
	 * 	 this section at the same time!
	 */
	static LvmCapabilities caps;

	return &caps;
    }


    string
    LvmCapabilities::get_ignoreactivationskip() const
    {
	return ignoreactivationskip;
    }


    bool
    LvmCapabilities::get_time_support() const
    {
	return time_support;
    }

}
