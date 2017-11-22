#!/usr/bin/python

import imp
stumpless_module = imp.load_source('stumpless', 'lib/swig/stumpless.py')

version = stumpless_module.get_stumpless_version()

if version.major != stumpless_module.STUMPLESS_MAJOR_VERSION:
  print("major version attribute did not match module attribute")

if version.minor != stumpless_module.STUMPLESS_MINOR_VERSION:

  print("minor version attribute did not match module attribute")

if version.patch != stumpless_module.STUMPLESS_PATCH_VERSION:
  print("patch version attribute did not match module attribute")
