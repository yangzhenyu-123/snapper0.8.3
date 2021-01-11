/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Path of chattr program. */
#define CHATTRBIN "/usr/bin/chattr"

/* Path of chsnap program. */
#define CHSNAPBIN "/sbin/chsnap"

/* Path of cp program. */
#define CPBIN "/bin/cp"

/* Path of diff program. */
#define DIFFBIN "/usr/bin/diff"

/* Enable Btrfs internal snapshots support */
#define ENABLE_BTRFS 1

/* Enable btrfs quota support */
/* #undef ENABLE_BTRFS_QUOTA */

/* Enable Ext4 snapshots support */
#define ENABLE_EXT4 1

/* Enable LVM thin-provisioned snapshots support */
#define ENABLE_LVM 1

/* Enable rollback support */
/* #undef ENABLE_ROLLBACK */

/* Enable SELinux support */
/* #undef ENABLE_SELINUX */

/* Enable extended attributes support */
#define ENABLE_XATTRS 1

/* Define to 1 if you have the <btrfs/version.h> header file. */
/* #undef HAVE_BTRFS_VERSION_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `btrfs' library (-lbtrfs). */
/* #undef HAVE_LIBBTRFS */

/* Define to 1 if you have the `selinux' library (-lselinux). */
/* #undef HAVE_LIBSELINUX */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Path of lvchange program. */
#define LVCHANGEBIN "/sbin/lvchange"

/* Path of lvcreate program. */
#define LVCREATEBIN "/sbin/lvcreate"

/* Path of lvm program. */
#define LVMBIN "/sbin/lvm"

/* Path of lvremove program. */
#define LVREMOVEBIN "/sbin/lvremove"

/* Path of lvrename program. */
#define LVRENAMEBIN "/sbin/lvrename"

/* Path of lvs program. */
#define LVSBIN "/sbin/lvs"

/* Name of package */
#define PACKAGE "snapper"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Path of rm program. */
#define RMBIN "/bin/rm"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Path of touch program. */
#define TOUCHBIN "/usr/bin/touch"

/* Version number of package */
#define VERSION "0.8.3"
