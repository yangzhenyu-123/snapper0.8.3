/*
 * Copyright (c) [2011-2013] Novell, Inc.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <algorithm>
#include <boost/thread.hpp>

#include "snapper/Log.h"
#include "snapper/AppUtil.h"
#include "snapper/File.h"
#include "snapper/Compare.h"
#include "snapper/Exception.h"
#include "snapper/XAttributes.h"
#include "snapper/Acls.h"


namespace snapper
{
    using namespace std;


    bool
    cmpFilesContentReg(const SFile& file1, const struct stat& stat1, const SFile& file2,
		       const struct stat& stat2)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(" 
	<< file1.fullname() << ", stat1=" << stat1.st_mode << file2.fullname() << ", stat2=" << stat2.st_mode << ")");
	if (stat1.st_mtim.tv_sec == stat2.st_mtim.tv_sec && stat1.st_mtim.tv_nsec == stat2.st_mtim.tv_nsec)
	    return true;

	if (stat1.st_size != stat2.st_size)
	    return false;

	if (stat1.st_size == 0 && stat2.st_size == 0)
	    return true;

	if ((stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino))
	    return true;

	int fd1 = file1.open(O_RDONLY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC);
	if (fd1 < 0)
	{
	    y2err("open failed path:" << file1.fullname() << " errno:" << errno);
	    return false;
	}

	int fd2 = file2.open(O_RDONLY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC);
	if (fd2 < 0)
	{
	    y2err("open failed path:" << file2.fullname() << " errno:" << errno);
	    close(fd1);
	    return false;
	}

	posix_fadvise(fd1, 0, 0, POSIX_FADV_SEQUENTIAL);
	posix_fadvise(fd2, 0, 0, POSIX_FADV_SEQUENTIAL);

	static_assert(sizeof(off_t) >= 8, "off_t is too small");

	const off_t block_size = 4096;

	char block1[block_size];
	char block2[block_size];

	bool equal = true;

	off_t length = stat1.st_size;
	while (length > 0)
	{
	    off_t t = min(block_size, length);

	    ssize_t r1 = read(fd1, block1, t);
	    if (r1 != t)
	    {
		y2err("read failed path:" << file1.fullname() << " errno:" << errno);
		equal = false;
		break;
	    }

	    ssize_t r2 = read(fd2, block2, t);
	    if (r2 != t)
	    {
		y2err("read failed path:" << file2.fullname() << " errno:" << errno);
		equal = false;
		break;
	    }

	    if (memcmp(block1, block2, t) != 0)
	    {
		equal = false;
		break;
	    }

	    length -= t;
	}

	close(fd1);
	close(fd2);

	return equal;
    }


    bool
    cmpFilesContentLnk(const SFile& file1, const struct stat& stat1, const SFile& file2,
		       const struct stat& stat2)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(" 
		 << file1.fullname() << ", stat1=" << stat1.st_mode << file2.fullname() << ", stat2=" << stat2.st_mode << ")");
	if (stat1.st_mtim.tv_sec == stat2.st_mtim.tv_sec && stat1.st_mtim.tv_nsec == stat2.st_mtim.tv_nsec) //最后修改时间
	{
		cout << "最后修改时间stat1:" << stat1.st_mtim.tv_sec << "s   stat2:" << stat2.st_mtim.tv_sec << "s" << endl;
		return true;
	}
	    
	
	string tmp1;
	bool r1 = file1.readlink(tmp1);
	if (!r1)
	{
	    y2err("readlink failed path:" << file1.fullname() << " errno:" << errno);
	    return false;
	}

	string tmp2;
	bool r2 = file2.readlink(tmp2);
	if (!r2)
	{
	    y2err("readlink failed path:" << file2.fullname() << " errno:" << errno);
	    return false;
	}

	return tmp1 == tmp2;
    }


    bool
    cmpFilesContent(const SFile& file1, const struct stat& stat1, const SFile& file2,
		    const struct stat& stat2)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(" << file1.fullname() << ", stat1=" << stat1.st_mode << " ,"<< file2.fullname() << ", stat2=" << stat2.st_mode << ")");
	if ((stat1.st_mode & S_IFMT) != (stat2.st_mode & S_IFMT))
	    SN_THROW(LogicErrorException());

	switch (stat1.st_mode & S_IFMT)
	{
	    case S_IFREG:
		cout << "是一般文件：调用cmpFilesContentReg进行比较" << endl;
		return cmpFilesContentReg(file1, stat1, file2, stat2);

	    case S_IFLNK:
		cout << "是链接文件：调用cmpFilesContentLnk进行比较" << endl;
		return cmpFilesContentLnk(file1, stat1, file2, stat2);

	    default:
		return true;
	}
    }


    unsigned int
    cmpFiles(const SFile& file1, const struct stat& stat1, const SFile& file2,
	     const struct stat& stat2)
    {
		 y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ <<
		  "("<< file1.fullname() << ", stat1=" << stat1.st_mode << " ,"<< file2.fullname() << ", stat2=" << stat2.st_mode << ")");
	unsigned int status = 0;

        /*
         * NOTE: just for a consideration
         *
         * if both ctimes are in match, files should be same
         * ctime can be altered only by some debugfs tool and
         * on umounted fs (ext2,3,4, xfs). So this should be safe
         * unless root or CAP_SYS_ADMIN played with low-level fs
         * utilities, right?
         *
         * if ((stat1.st_ctime == stat2.st_ctime))
         *      return status;
         *
         */

	if ((stat1.st_mode & S_IFMT) != (stat2.st_mode & S_IFMT))
	{
	    status |= TYPE; //0100 文件类型
	}
	else
	{
		cout << "调用cmpFilesContent函数比较内容" << endl;
	    if (!cmpFilesContent(file1, stat1, file2, stat2))
		status |= CONTENT; //01000
	}

	if ((stat1.st_mode ^ stat2.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID |
					       S_ISGID | S_ISVTX))
	{
	    status |= PERMISSIONS; //010000 
	}

	if (stat1.st_uid != stat2.st_uid)
	{
	    status |= OWNER; //0100000
	}

	if (stat1.st_gid != stat2.st_gid)
	{
	    status |= GROUP; //01000000
	}

#ifdef ENABLE_XATTRS
	if (file1.xaSupported() && file2.xaSupported())
	{
	    status |= cmpFilesXattrs(file1, file2);
	}
#endif

	return status;
    }


    unsigned int
    cmpFiles(const SFile& file1, const SFile& file2)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << 
	"(" << file1.fullname()<< ", " << file2.fullname() << ")");
	struct stat stat1;
	cout << "获取文件1信息，保存到定义的stat1结构体中" << endl;
	int r1 = file1.stat(&stat1, AT_SYMLINK_NOFOLLOW);

	struct stat stat2;
	cout << "获取文件2信息，保存到定义的stat2结构体中" << endl;
	int r2 = file2.stat(&stat2, AT_SYMLINK_NOFOLLOW);

	if (r1 != 0 && r2 == 0)
	    return CREATED;

	if (r1 == 0 && r2 != 0)
	    return DELETED;

	if (r1 != 0)
	    SN_THROW(IOErrorException("stat failed path:" + file1.fullname()));

	if (r2 != 0)
	    SN_THROW(IOErrorException("lstat failed path:" + file2.fullname()));
	cout << "将获取到的stat传入cmpFiles进行下一步比较：" << endl;
	return cmpFiles(file1, stat1, file2, stat2);
    }


    bool
    filter(const string& name)
    {
	if (name == "/.snapshots")
	    return true;

	return false;
    }


    void
    listSubdirs(const SDir& dir, const string& path, unsigned int status, cmpdirs_cb_t cb)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << 
	"(dir, path:" << path << ", status:" << status << ")");
	boost::this_thread::interruption_point();

	vector<string> entries = dir.entries();

	for (vector<string>::const_iterator it = entries.begin(); it != entries.end(); ++it)
	{
	    cb(path + "/" + *it, status);

	    struct stat stat;
	    dir.stat(*it, &stat, AT_SYMLINK_NOFOLLOW);
	    if (S_ISDIR(stat.st_mode))
		listSubdirs(SDir(dir, *it), path + "/" + *it, status, cb);
	}
    }


    struct CmpData
    {
	dev_t dev1;
	dev_t dev2;
	cmpdirs_cb_t cb;
    };


    void
    cmpDirsWorker(const CmpData& cmp_data, const SDir& dir1, const SDir& dir2, const string& path);


    void
    lonesome(const SDir& dir, const string& path, const string& name, const struct stat& stat,
	     unsigned int status, cmpdirs_cb_t cb)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(dir=" << dir.fullname() << ", path:" << path << ", name:" << name << ", stat" << ", status:" << status <<", cb)");
	cb(path + "/" + name, status);

	if (S_ISDIR(stat.st_mode))
	{
		cout << "当前比较的是目录:" << endl;
		listSubdirs(SDir(dir, name), path + "/" + name, status, cb);
	}
    }


    void
    twosome(const CmpData& cmp_data, const SDir& dir1, const SDir& dir2, const string& path,
	    const string& name, const struct stat& stat1, const struct stat& stat2)
    {
		 y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(cmp_data , dir1:" << 
		 dir1.fullname() << ", dir2:" << dir2.fullname() << ", " << path << ", " << name << ", stat1="
		  << stat1.st_mode << ", stat2=" << stat2.st_mode << ")" );
	unsigned int status = 0;
	if (stat1.st_dev == cmp_data.dev1 && stat2.st_dev == cmp_data.dev2)
	{
		cout << "======调用cmpFiles对文件进行比较======" << endl;
	    status = cmpFiles(SFile(dir1, name), stat1, SFile(dir2, name), stat2);
		cout << "这里的比较主要是文件的stat值的比较："<<endl;
		cout << "status=0x" << setbase(16) << status << "  1:不相同， 0:相同" << endl;
	//	cout << "这里每一位代表一种属性，1 不相同， 0 相同" << endl;
		
	}


	if (status != 0) //
	{
		cout << "确认status！=0,有不同之处" << endl;	
	    cmp_data.cb(path + "/" + name, status);
	}

	if (!(status & TYPE))
	{
		
	    if (S_ISDIR(stat1.st_mode))
		if (stat1.st_dev == cmp_data.dev1 && stat2.st_dev == cmp_data.dev2)
		{
			cout << "TYPE不同，为目录，调用cmpDirsWorker" << endl;
			cmpDirsWorker(cmp_data, SDir(dir1, name), SDir(dir2, name), path + "/" + name);
		}
		    
	}
	else
	{
	    if (S_ISDIR(stat1.st_mode))
		if (stat1.st_dev == cmp_data.dev1)
		{
			cout << "dir1:TYPE相同,是目录，调用listSubdirs"<<endl;
			listSubdirs(SDir(dir1, name), path + "/" + name, DELETED, cmp_data.cb);
		}
		  

	    if (S_ISDIR(stat2.st_mode))
		if (stat2.st_dev == cmp_data.dev2)
		{
			cout << "dir2:TYPE相同,是目录，调用listSubdirs"<<endl;
			listSubdirs(SDir(dir2, name), path + "/" + name, CREATED, cmp_data.cb);
		}

	}
	cout << "======调用cmpFiles对文件进行比较结束======" << endl;
    }


    void
    cmpDirsWorker(const CmpData& cmp_data, const SDir& dir1, const SDir& dir2, const string& path)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ <<"(cmp_data.dev1=" << cmp_data.dev1<<", cmp_data.dev2=" << cmp_data.dev2 << ", dir1:"
	  << dir1.fullname() << ", dir2:" << dir2.fullname() << ")" );
	boost::this_thread::interruption_point();

	vector<string> entries1 = dir1.entries();
	y2err("首先调用sort对dir1和2中的文件进行排序:");
	sort(entries1.begin(), entries1.end());
	vector<string>::const_iterator first1 = entries1.begin();
	vector<string>::const_iterator last1 = entries1.end();

	vector<string> entries2 = dir2.entries();
	sort(entries2.begin(), entries2.end());
	vector<string>::const_iterator first2 = entries2.begin();
	vector<string>::const_iterator last2 = entries2.end();

	// y2err("打印dir1和 dir2：");
	// cout << "dir1: ";
	// for (int i = 0; i != entries1.size();++i)
	// cout << entries1[i] << " ";

	// cout << "\n";

	// cout << "dir2: ";
	// for (int j = 0; j != entries2.size();++j)
	// cout << entries2[j] << "  ";

	// cout << "\n";

	y2err("打印排序后的dir1:");
	int nnn=1;
	for(first1=entries1.begin(); first1 != last1; first1++)
	{
	   cout << "num[" << nnn << "] :" << *first1 <<endl;
	   nnn++;
	}
	y2err("");
	y2err("打印排序后的dir2:");
	int mmm=1;
	for(first2=entries2.begin(); first2 != last2; first2++)
	{
    cout << "num[" << mmm << "] :" << *first2 <<endl;
	mmm++;
	}


	first1 = entries1.begin();
	last1 = entries1.end();

	first2 = entries2.begin();
	last2 = entries2.end();

	y2err("");
	y2err("======================开始对排序后的文件进行比较============================");
	while (first1 != last1 || first2 != last2)
	{
		cout << "{ " << endl;
	    if (first1 != last1 && filter(path + "/" + *first1))
	    {
			cout << "跳过dir1中的.snapshots" << endl;
		++first1;
			cout << "} " << endl;
	    }
	    else if (first2 != last2 && filter(path + "/" + *first2))
	    {
		++first2;
		cout << "跳过dir2中的.snapshots" << endl;
			cout << "} " << endl;
	    }
	    else if (first1 == last1) //dir1目录为空
	    {
		y2err( "first1 == last1：快照卷=" << first1->c_str());
		struct stat stat2;
		dir2.stat(*first2, &stat2, AT_SYMLINK_NOFOLLOW); // TODO error check

		if (stat2.st_dev == cmp_data.dev2)
		{
			y2err("当dir1和dir2的磁盘设备号匹配相同后，调用lonesome函数 CREATED 也就是dir1没有 dir2中有");
			lonesome(dir2, path, *first2, stat2, CREATED, cmp_data.cb);
		}
		++first2;
			cout << "} " << endl;
	    }
	    else if (first2 == last2) //dir2为空
	    {
		y2err( "first2 == last2：当前卷=" <<first1->c_str());
		struct stat stat1;
		dir1.stat(*first1, &stat1, AT_SYMLINK_NOFOLLOW); // TODO error check

		if (stat1.st_dev == cmp_data.dev1)
		{
			y2err("当匹配后，调用lonesome函数 DELETED 也就是dir1有 dir2中没有");
			lonesome(dir1, path, *first1, stat1, DELETED, cmp_data.cb);
		}

		++first1;
			cout << "} " << endl;
	    }
	    else if (*first2 < *first1) //
	    {
		y2err( "*first1 > *first2：快照卷=  " <<first1->c_str()<< ", 当前卷=" <<first2->c_str() );
		struct stat stat2;
		dir2.stat(*first2, &stat2, AT_SYMLINK_NOFOLLOW); // TODO error check

		if (stat2.st_dev == cmp_data.dev2)
		    lonesome(dir2, path, *first2, stat2, CREATED, cmp_data.cb);

		++first2;
			cout << "} " << endl;
	    }
	    else if (*first1 < *first2)
	    {
		y2err( "*first1 < *first2：快照卷= " <<first1->c_str()<< ", 当前卷=" << first2->c_str());
		struct stat stat1;
		dir1.stat(*first1, &stat1, AT_SYMLINK_NOFOLLOW); // TODO error check

		if (stat1.st_dev == cmp_data.dev1)
		    lonesome(dir1, path, *first1, stat1, DELETED, cmp_data.cb);

		++first1;
			cout << "} " << endl;
	    }
	    else
	    {
		if (*first1 != *first2)
		    SN_THROW(LogicErrorException());

		struct stat stat1;
		dir1.stat(*first1, &stat1, AT_SYMLINK_NOFOLLOW); // TODO error check

		struct stat stat2;
		dir2.stat(*first2, &stat2, AT_SYMLINK_NOFOLLOW); // TODO error check
		y2err( "*first1 == *first2：快照卷= " << first1->c_str() << ", 当前卷=" << first2->c_str());
		twosome(cmp_data, dir1, dir2, path, *first1, stat1, stat2);
		++first1;
		++first2;
			cout << "}" << endl;
	    }
	}
    }


    void
    cmpDirs(const SDir& dir1, const SDir& dir2, cmpdirs_cb_t cb)
    {
	y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(dir1:" << dir1.fullname() << ", dir2:" << dir2.fullname() << ", cb)");
	y2mil("path1:" << dir1.fullname() << " path2:" << dir2.fullname());

	struct stat stat1;
	int r1 = dir1.stat(&stat1);
	if (r1 != 0)
	    SN_THROW(IOErrorException(sformat("stat failed path:%s errno:%d",
					      dir1.fullname().c_str(), errno)));

	struct stat stat2;
	int r2 = dir2.stat(&stat2);
	if (r2 != 0)
	    SN_THROW(IOErrorException(sformat("stat failed path:%s errno:%d",
					      dir2.fullname().c_str(), errno)));

    cout << "cmpdir1=" <<  dir1.fullname().c_str() << "  cmpdir2=" << dir2.fullname().c_str() << endl;
	CmpData cmp_data;
	cmp_data.cb = cb;
	cmp_data.dev1 = stat1.st_dev;
	cmp_data.dev2 = stat2.st_dev;

	y2mil("dev1:" << cmp_data.dev1 << "  dev2:" << cmp_data.dev2);
	y2err("cmp_data.dev1:" << cmp_data.dev1 << " cmp_data.dev2:" << cmp_data.dev2);
	StopWatch stopwatch;
	cout << "=======================cmpDirs调用cmpDirsWorker开始==========================" << endl;
	cmpDirsWorker(cmp_data, dir1, dir2, "");
	cout << "========================cmpDirs调用cmpDirsWorker结束=======================" << endl;
	y2mil("stopwatch " << stopwatch << " for comparing directories");
    }


    unsigned int
    cmpFilesXattrs(const SFile& file1, const SFile& file2)
    {
		 y2err("snapper/" << __FILE__ << "|| func name:" << __FUNCTION__ << "(file1, file2)");
        try
        {
	    XAttributes xa(file1);
	    XAttributes xb(file2);

	    if (xa == xb)
	    {
		return 0;
	    }
	    else
	    {
		unsigned int status = XATTRS;

		CompareAcls acl_a(xa);
		CompareAcls acl_b(xb);

		status |= (acl_a == acl_b) ? 0 : ACL;

		return status;
	    }
        }
	catch (const XAttributesException& e)
        {
	    y2err("extended attributes or ACL compare failed");
	    return (XATTRS | ACL);
	}
    }

}
