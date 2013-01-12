#!/bin/sh

autoreconf \
&& mkdir build \
&& cd build \
&& ../configure \
&& make \
&& make check
