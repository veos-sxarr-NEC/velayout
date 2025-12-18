#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([velayout], [3.6.0], [t-aoyama@ap.jp.nec.com])
AC_CONFIG_SRCDIR([src/velayout.c])
AC_CONFIG_SRCDIR([src/velayout.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([./build-aux])

AC_SUBST(RELEASE)
AC_ARG_WITH([release-id], [AS_HELP_STRING([--with-release-id],
            [Specify release id])],
            [RELEASE=${with_release_id}],
            [RELEASE="1"])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_PROG_AR
LT_INIT
AC_CONFIG_MACRO_DIR([m4])
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_CHECK_LIB([log4c],[log4c_init],[],
		[AC_MSG_ERROR([log4c library support missing/incomplete])])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
		 velayout.spec
		 src/Makefile
		 debian/rules
		 debian/control
		 debian/velayout.install
		 debian/velayout-dev.install])
AC_OUTPUT
