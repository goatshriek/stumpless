#!/bin/sh

# destroy the build directory
rm -rf build

# remove the autoconf files
rm -rf autom4te.cache

# remove the documentation
rm -rf doc/html

rm -f configure
rm -f Makefile.in
rm -f include/stumpless/config/check.h.in
rm -f include/stumpless/config/check.h.in~
