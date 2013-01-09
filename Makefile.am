AUTOMAKE_OPTIONS = -Wall -Werror

ACLOCAL_AMFLAGS = -I m4

vpath %.h include
vpath %.c src test/function test/performance test/portability

AM_CFLAGS = -I $(top_srcdir)/include

stumpless_includedir = $(pkgincludedir)
stumpless_include_HEADERS = include/logger.h \
                            include/stumpless.h \
                            include/types.h

include src/Makefile.am
include test/Makefile.am
