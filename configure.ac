AC_PREREQ([2.68])

AC_INIT([stumpless], [0.0.1], [joelanderson3@yahoo.com])

AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([src/logger.c])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile])

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

LT_INIT

AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h stdio.h string.h time.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# enable arguments
AC_ARG_ENABLE([namespace],
  [AS_HELP_STRING([--enable-namespace],
    [append a prefix to all functions])],
  [namespace=$enableval],
  [namespace=Stumpless]
)

AC_DEFINE_UNQUOTED([NMSPC],
                   $namespace,
                   [namespace to append to public library members])

AC_OUTPUT
