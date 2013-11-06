AUTOMAKE_OPTIONS = -Wall subdir-objects parallel-tests color-tests

ACLOCAL_AMFLAGS = -I m4

vpath %.h include include/stumpless include/private test/include
vpath %.c src test/function test/helper test/performance test/portability

include include/Makefile.am
include src/Makefile.am
include test/Makefile.am
