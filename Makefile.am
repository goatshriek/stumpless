AUTOMAKE_OPTIONS = -Wall subdir-objects parallel-tests color-tests

ACLOCAL_AMFLAGS = -I m4

vpath %.h include
vpath %.c src test/function test/performance test/portability

AM_CFLAGS = -I $(top_srcdir)/include

stumpless_includedir = $(pkgincludedir)
stumpless_include_HEADERS = include/boolean.h \
                            include/configuration.h \
                            include/entry.h \
                            include/event.h \
                            include/file_output.h \
                            include/level.h \
                            include/logger.h \
                            include/status.h \
                            include/stumpless.h \
                            include/text_formatter.h \
                            include/types.h \
                            include/value.h \
                            include/value_list.h

include src/Makefile.am
include test/Makefile.am
