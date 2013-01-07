#!/bin/sh

# destroy the build directory
rm -rf build

# remove the autoconf files
rm -rf autom4te.cache
rm configure
rm Makefile.in
