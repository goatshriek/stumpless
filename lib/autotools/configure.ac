AC_INIT

AC_CONFIG_HEADERS([config.h:config.h.in])

AC_LANG_PUSH([C++])
AC_CHECK_HEADER([gtest/gtest.h], [AC_DEFINE([__STUMPLESS_HAVE_LIB_GTEST],
    [1],
    [define if gtest header is available])])
AC_LANG_POP([C++])

AC_OUTPUT
