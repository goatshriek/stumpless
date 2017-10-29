#!/usr/bin/python

import imp
foo = imp.load_source('stumpless', 'lib/swig/stumpless.py')
foo.stumpless("testing of the python extension")
