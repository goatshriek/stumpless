#!/bin/sh

# destroy the build directory
rm -rf build

# remove the autoconf files
rm -rf autom4te.cache

rm -f configure
rm -f Makefile.in
rm -f include/stumpless/config.h.in
rm -f include/stumpless/config.h.in~
