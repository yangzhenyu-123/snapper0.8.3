# Makefile.in generated by automake 1.16.1 from Makefile.am.
# client/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2018 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



#
# Makefile.am for snapper/client
#


am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/snapper
pkgincludedir = $(includedir)/snapper
pkglibdir = $(libdir)/snapper
pkglibexecdir = $(libexecdir)/snapper
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-pc-linux-gnu
host_triplet = x86_64-pc-linux-gnu
bin_PROGRAMS = snapper$(EXEEXT)
libexec_PROGRAMS = systemd-helper$(EXEEXT) $(am__EXEEXT_1)
am__append_1 = installation-helper
#sbin_PROGRAMS =  \
#	mksubvolume$(EXEEXT)
subdir = client
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(am__DIST_COMMON)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__installdirs = "$(DESTDIR)$(bindir)" "$(DESTDIR)$(libexecdir)" \
	"$(DESTDIR)$(sbindir)"
am__EXEEXT_1 = installation-helper$(EXEEXT)
PROGRAMS = $(bin_PROGRAMS) $(libexec_PROGRAMS) $(sbin_PROGRAMS)
am__installation_helper_SOURCES_DIST = installation-helper.cc misc.cc \
	misc.h
am_installation_helper_OBJECTS =  \
	installation-helper.$(OBJEXT) \
	misc.$(OBJEXT)
installation_helper_OBJECTS = $(am_installation_helper_OBJECTS)
installation_helper_DEPENDENCIES =  \
	../snapper/libsnapper.la utils/libutils.la
AM_V_lt = $(am__v_lt_$(V))
am__v_lt_ = $(am__v_lt_$(AM_DEFAULT_VERBOSITY))
am__v_lt_0 = --silent
am__v_lt_1 = 
am__mksubvolume_SOURCES_DIST = mksubvolume.cc
#am_mksubvolume_OBJECTS = mksubvolume.$(OBJEXT)
mksubvolume_OBJECTS = $(am_mksubvolume_OBJECTS)
#mksubvolume_DEPENDENCIES = ../snapper/libsnapper.la \
#	utils/libutils.la
am_snapper_OBJECTS = snapper.$(OBJEXT) types.$(OBJEXT) \
	commands.$(OBJEXT) cleanup.$(OBJEXT) proxy.$(OBJEXT) \
	proxy-dbus.$(OBJEXT) proxy-lib.$(OBJEXT) misc.$(OBJEXT) \
	errors.$(OBJEXT)
snapper_OBJECTS = $(am_snapper_OBJECTS)
snapper_DEPENDENCIES = ../snapper/libsnapper.la utils/libutils.la \
	../dbus/libdbus.la
am_systemd_helper_OBJECTS = systemd-helper.$(OBJEXT) types.$(OBJEXT) \
	commands.$(OBJEXT) cleanup.$(OBJEXT) proxy.$(OBJEXT) \
	proxy-dbus.$(OBJEXT) proxy-lib.$(OBJEXT) misc.$(OBJEXT) \
	errors.$(OBJEXT)
systemd_helper_OBJECTS = $(am_systemd_helper_OBJECTS)
systemd_helper_DEPENDENCIES = ../snapper/libsnapper.la \
	utils/libutils.la ../dbus/libdbus.la
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__maybe_remake_depfiles = depfiles
am__depfiles_remade = ./$(DEPDIR)/cleanup.Po ./$(DEPDIR)/commands.Po \
	./$(DEPDIR)/errors.Po ./$(DEPDIR)/installation-helper.Po \
	./$(DEPDIR)/misc.Po ./$(DEPDIR)/mksubvolume.Po \
	./$(DEPDIR)/proxy-dbus.Po ./$(DEPDIR)/proxy-lib.Po \
	./$(DEPDIR)/proxy.Po ./$(DEPDIR)/snapper.Po \
	./$(DEPDIR)/systemd-helper.Po ./$(DEPDIR)/types.Po
am__mv = mv -f
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CXX) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS)
AM_V_CXX = $(am__v_CXX_$(V))
am__v_CXX_ = $(am__v_CXX_$(AM_DEFAULT_VERBOSITY))
am__v_CXX_0 = @echo "  CXX     " $@;
am__v_CXX_1 = 
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CXXLD = $(am__v_CXXLD_$(V))
am__v_CXXLD_ = $(am__v_CXXLD_$(AM_DEFAULT_VERBOSITY))
am__v_CXXLD_0 = @echo "  CXXLD   " $@;
am__v_CXXLD_1 = 
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CC) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 = 
CCLD = $(CC)
LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 = 
SOURCES = $(installation_helper_SOURCES) $(mksubvolume_SOURCES) \
	$(snapper_SOURCES) $(systemd_helper_SOURCES)
DIST_SOURCES = $(am__installation_helper_SOURCES_DIST) \
	$(am__mksubvolume_SOURCES_DIST) $(snapper_SOURCES) \
	$(systemd_helper_SOURCES)
RECURSIVE_TARGETS = all-recursive check-recursive cscopelist-recursive \
	ctags-recursive dvi-recursive html-recursive info-recursive \
	install-data-recursive install-dvi-recursive \
	install-exec-recursive install-html-recursive \
	install-info-recursive install-pdf-recursive \
	install-ps-recursive install-recursive installcheck-recursive \
	installdirs-recursive pdf-recursive ps-recursive \
	tags-recursive uninstall-recursive
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
RECURSIVE_CLEAN_TARGETS = mostlyclean-recursive clean-recursive	\
  distclean-recursive maintainer-clean-recursive
am__recursive_targets = \
  $(RECURSIVE_TARGETS) \
  $(RECURSIVE_CLEAN_TARGETS) \
  $(am__extra_recursive_targets)
AM_RECURSIVE_TARGETS = $(am__recursive_targets:-recursive=) TAGS CTAGS \
	distdir distdir-am
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP)
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
ETAGS = etags
CTAGS = ctags
DIST_SUBDIRS = $(SUBDIRS)
am__DIST_COMMON = $(srcdir)/Makefile.in $(top_srcdir)/depcomp
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
am__relativize = \
  dir0=`pwd`; \
  sed_first='s,^\([^/]*\)/.*$$,\1,'; \
  sed_rest='s,^[^/]*/*,,'; \
  sed_last='s,^.*/\([^/]*\)$$,\1,'; \
  sed_butlast='s,/*[^/]*$$,,'; \
  while test -n "$$dir1"; do \
    first=`echo "$$dir1" | sed -e "$$sed_first"`; \
    if test "$$first" != "."; then \
      if test "$$first" = ".."; then \
        dir2=`echo "$$dir0" | sed -e "$$sed_last"`/"$$dir2"; \
        dir0=`echo "$$dir0" | sed -e "$$sed_butlast"`; \
      else \
        first2=`echo "$$dir2" | sed -e "$$sed_first"`; \
        if test "$$first2" = "$$first"; then \
          dir2=`echo "$$dir2" | sed -e "$$sed_rest"`; \
        else \
          dir2="../$$dir2"; \
        fi; \
        dir0="$$dir0"/"$$first"; \
      fi; \
    fi; \
    dir1=`echo "$$dir1" | sed -e "$$sed_rest"`; \
  done; \
  reldir="$$dir2"
ACLOCAL = ${SHELL} /root/snapper-0.8.3/missing aclocal-1.16
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 1
AR = ar
AUTOCONF = ${SHELL} /root/snapper-0.8.3/missing autoconf
AUTOHEADER = ${SHELL} /root/snapper-0.8.3/missing autoheader
AUTOMAKE = ${SHELL} /root/snapper-0.8.3/missing automake-1.16
AWK = gawk
CC = gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -Wl,-rpath= -std=c99 -Wall -Wextra -Wformat -Wmissing-prototypes -Wno-unused-parameter
CHATTRBIN = /usr/bin/chattr
CHSNAPBIN = /sbin/chsnap
CPBIN = /bin/cp
CPP = gcc -E
CPPFLAGS = -I/root/boost/boost1.55-1.55.0+dfs -DCONFDIR='"/etc/sysconfig"'
CXX = g++
CXXCPP = g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -Wl,-rpath= -std=c++11 -Wall -Wextra -Wformat -Wnon-virtual-dtor -Wno-unused-parameter
CYGPATH_W = echo
DBUS_CFLAGS = -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include 
DBUS_LIBS = -ldbus-1 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DIFFBIN = /usr/bin/diff
DLLTOOL = false
DSYMUTIL = 
DUMPBIN = 
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
FGREP = /bin/grep -F
GREP = /bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LD = /usr/bin/ld -m elf_x86_64
LDFLAGS = -L/root/boost/boost1.55-1.55.0+dfs/stage/lib/
LIBOBJS = 
LIBS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBVERSION_INFO = 10:0:6
LIBVERSION_MAJOR = 4
LIBVERSION_MINOR = 6
LIBVERSION_PATCHLEVEL = 0
LIPO = 
LN_S = ln -s
LTLIBOBJS = 
LT_SYS_LIBRARY_PATH = 
LVCHANGEBIN = /sbin/lvchange
LVCREATEBIN = /sbin/lvcreate
LVMBIN = /sbin/lvm
LVREMOVEBIN = /sbin/lvremove
LVRENAMEBIN = /sbin/lvrename
LVSBIN = /sbin/lvs
MAKEINFO = ${SHELL} /root/snapper-0.8.3/missing makeinfo
MANIFEST_TOOL = :
MKDIR_P = /bin/mkdir -p
NM = /usr/bin/nm -B
NMEDIT = 
OBJDUMP = objdump
OBJEXT = o
OTOOL = 
OTOOL64 = 
PACKAGE = snapper
PACKAGE_BUGREPORT = 
PACKAGE_NAME = 
PACKAGE_STRING = 
PACKAGE_TARNAME = 
PACKAGE_URL = 
PACKAGE_VERSION = 
PATH_SEPARATOR = :
PKG_CONFIG = /usr/bin/pkg-config
PKG_CONFIG_LIBDIR = 
PKG_CONFIG_PATH = 
RANLIB = ranlib
RMBIN = /bin/rm
SED = /bin/sed
SET_MAKE = 
SHELL = /bin/sh
STRIP = strip
SYSCONFIG = /etc/sysconfig
TOUCHBIN = /usr/bin/touch
VERSION = 0.8.3
XSLTPROC = /usr/bin/xsltproc
abs_builddir = /root/snapper-0.8.3/client
abs_srcdir = /root/snapper-0.8.3/client
abs_top_builddir = /root/snapper-0.8.3
abs_top_srcdir = /root/snapper-0.8.3
ac_ct_AR = ar
ac_ct_CC = gcc
ac_ct_CXX = g++
ac_ct_DUMPBIN = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build = x86_64-pc-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = pc
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = x86_64-pc-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux-gnu
host_vendor = pc
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /root/snapper-0.8.3/install-sh
libdir = ${exec_prefix}/lib
libexecdir = /usr/lib/snapper
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local/linxsnap
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../
top_builddir = ..
top_srcdir = ..
SUBDIRS = utils
AM_CPPFLAGS = -I$(top_srcdir) $(DBUS_CFLAGS)
snapper_SOURCES = \
	snapper.cc			\
	types.cc	types.h		\
	commands.cc	commands.h	\
	cleanup.cc	cleanup.h	\
	proxy.cc	proxy.h		\
	proxy-dbus.cc	proxy-dbus.h	\
	proxy-lib.cc	proxy-lib.h	\
	misc.cc		misc.h		\
	errors.cc	errors.h

snapper_LDADD = ../snapper/libsnapper.la utils/libutils.la ../dbus/libdbus.la
systemd_helper_SOURCES = \
	systemd-helper.cc		\
	types.cc	types.h		\
	commands.cc	commands.h	\
	cleanup.cc	cleanup.h	\
	proxy.cc	proxy.h		\
	proxy-dbus.cc	proxy-dbus.h	\
	proxy-lib.cc	proxy-lib.h	\
	misc.cc		misc.h		\
	errors.cc	errors.h

systemd_helper_LDADD = ../snapper/libsnapper.la utils/libutils.la ../dbus/libdbus.la
installation_helper_SOURCES = \
	installation-helper.cc		\
	misc.cc		misc.h

installation_helper_LDADD = ../snapper/libsnapper.la utils/libutils.la
#mksubvolume_SOURCES = \
#	mksubvolume.cc

#mksubvolume_LDADD = ../snapper/libsnapper.la utils/libutils.la
all: all-recursive

.SUFFIXES:
.SUFFIXES: .cc .lo .o .obj
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu client/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --gnu client/Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__maybe_remake_depfiles)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__maybe_remake_depfiles);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(bindir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(bindir)" || exit 1; \
	fi; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p \
	 || test -f $$p1 \
	  ; then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' \
	    -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	    echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(bindir)$$dir'"; \
	    $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' \
	`; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(bindir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(bindir)" && rm -f $$files

clean-binPROGRAMS:
	@list='$(bin_PROGRAMS)'; test -n "$$list" || exit 0; \
	echo " rm -f" $$list; \
	rm -f $$list || exit $$?; \
	test -n "$(EXEEXT)" || exit 0; \
	list=`for p in $$list; do echo "$$p"; done | sed 's/$(EXEEXT)$$//'`; \
	echo " rm -f" $$list; \
	rm -f $$list
install-libexecPROGRAMS: $(libexec_PROGRAMS)
	@$(NORMAL_INSTALL)
	@list='$(libexec_PROGRAMS)'; test -n "$(libexecdir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(libexecdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libexecdir)" || exit 1; \
	fi; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p \
	 || test -f $$p1 \
	  ; then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' \
	    -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	    echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(libexecdir)$$dir'"; \
	    $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(libexecdir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-libexecPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(libexec_PROGRAMS)'; test -n "$(libexecdir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' \
	`; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(libexecdir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(libexecdir)" && rm -f $$files

clean-libexecPROGRAMS:
	@list='$(libexec_PROGRAMS)'; test -n "$$list" || exit 0; \
	echo " rm -f" $$list; \
	rm -f $$list || exit $$?; \
	test -n "$(EXEEXT)" || exit 0; \
	list=`for p in $$list; do echo "$$p"; done | sed 's/$(EXEEXT)$$//'`; \
	echo " rm -f" $$list; \
	rm -f $$list
install-sbinPROGRAMS: $(sbin_PROGRAMS)
	@$(NORMAL_INSTALL)
	@list='$(sbin_PROGRAMS)'; test -n "$(sbindir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(sbindir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(sbindir)" || exit 1; \
	fi; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p \
	 || test -f $$p1 \
	  ; then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' \
	    -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	    echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(sbindir)$$dir'"; \
	    $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(sbindir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-sbinPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(sbin_PROGRAMS)'; test -n "$(sbindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' \
	`; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(sbindir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(sbindir)" && rm -f $$files

clean-sbinPROGRAMS:
	@list='$(sbin_PROGRAMS)'; test -n "$$list" || exit 0; \
	echo " rm -f" $$list; \
	rm -f $$list || exit $$?; \
	test -n "$(EXEEXT)" || exit 0; \
	list=`for p in $$list; do echo "$$p"; done | sed 's/$(EXEEXT)$$//'`; \
	echo " rm -f" $$list; \
	rm -f $$list

installation-helper$(EXEEXT): $(installation_helper_OBJECTS) $(installation_helper_DEPENDENCIES) $(EXTRA_installation_helper_DEPENDENCIES) 
	@rm -f installation-helper$(EXEEXT)
	$(AM_V_CXXLD)$(CXXLINK) $(installation_helper_OBJECTS) $(installation_helper_LDADD) $(LIBS)

mksubvolume$(EXEEXT): $(mksubvolume_OBJECTS) $(mksubvolume_DEPENDENCIES) $(EXTRA_mksubvolume_DEPENDENCIES) 
	@rm -f mksubvolume$(EXEEXT)
	$(AM_V_CXXLD)$(CXXLINK) $(mksubvolume_OBJECTS) $(mksubvolume_LDADD) $(LIBS)

snapper$(EXEEXT): $(snapper_OBJECTS) $(snapper_DEPENDENCIES) $(EXTRA_snapper_DEPENDENCIES) 
	@rm -f snapper$(EXEEXT)
	$(AM_V_CXXLD)$(CXXLINK) $(snapper_OBJECTS) $(snapper_LDADD) $(LIBS)

systemd-helper$(EXEEXT): $(systemd_helper_OBJECTS) $(systemd_helper_DEPENDENCIES) $(EXTRA_systemd_helper_DEPENDENCIES) 
	@rm -f systemd-helper$(EXEEXT)
	$(AM_V_CXXLD)$(CXXLINK) $(systemd_helper_OBJECTS) $(systemd_helper_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/cleanup.Po # am--include-marker
include ./$(DEPDIR)/commands.Po # am--include-marker
include ./$(DEPDIR)/errors.Po # am--include-marker
include ./$(DEPDIR)/installation-helper.Po # am--include-marker
include ./$(DEPDIR)/misc.Po # am--include-marker
include ./$(DEPDIR)/mksubvolume.Po # am--include-marker
include ./$(DEPDIR)/proxy-dbus.Po # am--include-marker
include ./$(DEPDIR)/proxy-lib.Po # am--include-marker
include ./$(DEPDIR)/proxy.Po # am--include-marker
include ./$(DEPDIR)/snapper.Po # am--include-marker
include ./$(DEPDIR)/systemd-helper.Po # am--include-marker
include ./$(DEPDIR)/types.Po # am--include-marker

$(am__depfiles_remade):
	@$(MKDIR_P) $(@D)
	@echo '# dummy' >$@-t && $(am__mv) $@-t $@

am--depfiles: $(am__depfiles_remade)

.cc.o:
	$(AM_V_CXX)$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CXX)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(AM_V_CXX_no)$(CXXCOMPILE) -c -o $@ $<

.cc.obj:
	$(AM_V_CXX)$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CXX)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(AM_V_CXX_no)$(CXXCOMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.cc.lo:
	$(AM_V_CXX)$(LTCXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	$(AM_V_CXX)source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(AM_V_CXX_no)$(LTCXXCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

# This directory's subdirectories are mostly independent; you can cd
# into them and run 'make' without going through this Makefile.
# To change the values of 'make' variables: instead of editing Makefiles,
# (1) if the variable is set in 'config.status', edit 'config.status'
#     (which will cause the Makefiles to be regenerated when you run 'make');
# (2) otherwise, pass the desired values on the 'make' command line.
$(am__recursive_targets):
	@fail=; \
	if $(am__make_keepgoing); then \
	  failcom='fail=yes'; \
	else \
	  failcom='exit 1'; \
	fi; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	case "$@" in \
	  distclean-* | maintainer-clean-*) list='$(DIST_SUBDIRS)' ;; \
	  *) list='$(SUBDIRS)' ;; \
	esac; \
	for subdir in $$list; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  ($(am__cd) $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	  || eval $$failcom; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

ID: $(am__tagged_files)
	$(am__define_uniq_tagged_files); mkid -fID $$unique
tags: tags-recursive
TAGS: tags

tags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	set x; \
	here=`pwd`; \
	if ($(ETAGS) --etags-include --version) >/dev/null 2>&1; then \
	  include_option=--etags-include; \
	  empty_fix=.; \
	else \
	  include_option=--include; \
	  empty_fix=; \
	fi; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test ! -f $$subdir/TAGS || \
	      set "$$@" "$$include_option=$$here/$$subdir/TAGS"; \
	  fi; \
	done; \
	$(am__define_uniq_tagged_files); \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: ctags-recursive

CTAGS: ctags
ctags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	$(am__define_uniq_tagged_files); \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
cscopelist: cscopelist-recursive

cscopelist-am: $(am__tagged_files)
	list='$(am__tagged_files)'; \
	case "$(srcdir)" in \
	  [\\/]* | ?:[\\/]*) sdir="$(srcdir)" ;; \
	  *) sdir=$(subdir)/$(srcdir) ;; \
	esac; \
	for i in $$list; do \
	  if test -f "$$i"; then \
	    echo "$(subdir)/$$i"; \
	  else \
	    echo "$$sdir/$$i"; \
	  fi; \
	done >> $(top_builddir)/cscope.files

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) distdir-am

distdir-am: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
	@list='$(DIST_SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    $(am__make_dryrun) \
	      || test -d "$(distdir)/$$subdir" \
	      || $(MKDIR_P) "$(distdir)/$$subdir" \
	      || exit 1; \
	    dir1=$$subdir; dir2="$(distdir)/$$subdir"; \
	    $(am__relativize); \
	    new_distdir=$$reldir; \
	    dir1=$$subdir; dir2="$(top_distdir)"; \
	    $(am__relativize); \
	    new_top_distdir=$$reldir; \
	    echo " (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) top_distdir="$$new_top_distdir" distdir="$$new_distdir" \\"; \
	    echo "     am__remove_distdir=: am__skip_length_check=: am__skip_mode_fix=: distdir)"; \
	    ($(am__cd) $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$$new_top_distdir" \
	        distdir="$$new_distdir" \
		am__remove_distdir=: \
		am__skip_length_check=: \
		am__skip_mode_fix=: \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-recursive
all-am: Makefile $(PROGRAMS)
installdirs: installdirs-recursive
installdirs-am:
	for dir in "$(DESTDIR)$(bindir)" "$(DESTDIR)$(libexecdir)" "$(DESTDIR)$(sbindir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-recursive
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-recursive
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-recursive

clean-am: clean-binPROGRAMS clean-generic clean-libexecPROGRAMS \
	clean-libtool clean-sbinPROGRAMS mostlyclean-am

distclean: distclean-recursive
		-rm -f ./$(DEPDIR)/cleanup.Po
	-rm -f ./$(DEPDIR)/commands.Po
	-rm -f ./$(DEPDIR)/errors.Po
	-rm -f ./$(DEPDIR)/installation-helper.Po
	-rm -f ./$(DEPDIR)/misc.Po
	-rm -f ./$(DEPDIR)/mksubvolume.Po
	-rm -f ./$(DEPDIR)/proxy-dbus.Po
	-rm -f ./$(DEPDIR)/proxy-lib.Po
	-rm -f ./$(DEPDIR)/proxy.Po
	-rm -f ./$(DEPDIR)/snapper.Po
	-rm -f ./$(DEPDIR)/systemd-helper.Po
	-rm -f ./$(DEPDIR)/types.Po
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-recursive

dvi-am:

html: html-recursive

html-am:

info: info-recursive

info-am:

install-data-am:

install-dvi: install-dvi-recursive

install-dvi-am:

install-exec-am: install-binPROGRAMS install-libexecPROGRAMS \
	install-sbinPROGRAMS

install-html: install-html-recursive

install-html-am:

install-info: install-info-recursive

install-info-am:

install-man:

install-pdf: install-pdf-recursive

install-pdf-am:

install-ps: install-ps-recursive

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-recursive
		-rm -f ./$(DEPDIR)/cleanup.Po
	-rm -f ./$(DEPDIR)/commands.Po
	-rm -f ./$(DEPDIR)/errors.Po
	-rm -f ./$(DEPDIR)/installation-helper.Po
	-rm -f ./$(DEPDIR)/misc.Po
	-rm -f ./$(DEPDIR)/mksubvolume.Po
	-rm -f ./$(DEPDIR)/proxy-dbus.Po
	-rm -f ./$(DEPDIR)/proxy-lib.Po
	-rm -f ./$(DEPDIR)/proxy.Po
	-rm -f ./$(DEPDIR)/snapper.Po
	-rm -f ./$(DEPDIR)/systemd-helper.Po
	-rm -f ./$(DEPDIR)/types.Po
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-recursive

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-recursive

pdf-am:

ps: ps-recursive

ps-am:

uninstall-am: uninstall-binPROGRAMS uninstall-libexecPROGRAMS \
	uninstall-sbinPROGRAMS

.MAKE: $(am__recursive_targets) install-am install-strip

.PHONY: $(am__recursive_targets) CTAGS GTAGS TAGS all all-am \
	am--depfiles check check-am clean clean-binPROGRAMS \
	clean-generic clean-libexecPROGRAMS clean-libtool \
	clean-sbinPROGRAMS cscopelist-am ctags ctags-am distclean \
	distclean-compile distclean-generic distclean-libtool \
	distclean-tags distdir dvi dvi-am html html-am info info-am \
	install install-am install-binPROGRAMS install-data \
	install-data-am install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-libexecPROGRAMS install-man \
	install-pdf install-pdf-am install-ps install-ps-am \
	install-sbinPROGRAMS install-strip installcheck \
	installcheck-am installdirs installdirs-am maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool pdf pdf-am ps ps-am \
	tags tags-am uninstall uninstall-am uninstall-binPROGRAMS \
	uninstall-libexecPROGRAMS uninstall-sbinPROGRAMS

.PRECIOUS: Makefile


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
