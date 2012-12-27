#!/bin/sh

# destroy the build directory
rm -rf build

# remove the autoconf files
rm aclocal.m4
rm -rf autom4te.cache
rm configure
rm Makefile.in
rm src/Makefile.in
