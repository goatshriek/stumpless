#!/bin/sh

aclocal \
&& automake --add-missing \
&& autoconf \
&& mkdir build \
&& cd build \
&& ../configure
