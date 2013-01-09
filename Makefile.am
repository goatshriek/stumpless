AUTOMAKE_OPTIONS = -Wall -Werror

ACLOCAL_AMFLAGS = -I m4

vpath %.h include
vpath %.c src

stumpless_includedir = $(pkgincludedir)
stumpless_include_HEADERS = include/stumpless.h \
                            include/logger.h \
                            include/types.h

include src/Makefile.am
include test/Makefile.am
