#Copyright 2018 Joel E. Anderson
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.

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
