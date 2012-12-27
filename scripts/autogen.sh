#!/bin/sh

aclocal && automake && autoconf && mkdir build && cd build && ../configure
