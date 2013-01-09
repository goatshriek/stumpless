# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])

AC_INIT([stumpless], [0.0.1], [joelanderson3@yahoo.com])
LT_INIT

AC_CONFIG_SRCDIR([src/logger.c])
AC_CONFIG_FILES([Makefile])i

# todo - need to fix the AC_CONFIG_AUX_DIR macr to work
#AC_CONFIG_AUX_DIR([config])

AC_CONFIG_HEADERS([include/config.h])

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
