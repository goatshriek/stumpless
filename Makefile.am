AUTOMAKE_OPTIONS = -Wall subdir-objects parallel-tests color-tests

ACLOCAL_AMFLAGS = -I m4

vpath %.h include test/include
vpath %.c src test/function test/helper test/performance test/portability

AM_CFLAGS = -g -I $(top_srcdir)/include

stumpless_includedir = $(pkgincludedir)

include include/Makefile.am
include src/Makefile.am
include test/Makefile.am
