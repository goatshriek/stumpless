# Copyright 2024 Joel E. Anderson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# this script assumes that you are in a build folder that has already been
# configured with cmake and has C++ enabled

sourcedir=$(grep -E '.*_SOURCE_DIR:STATIC=.*' CMakeCache.txt | grep -E -o '/.*')
majorvers=$( grep 'PROJECT_VERSION_MAJOR' CMakeCache.txt | grep -E -o '[[:digit:]]+$')
minorvers=$( grep 'PROJECT_VERSION_MINOR' CMakeCache.txt | grep -E -o '[[:digit:]]+$')
patchvers=$( grep 'PROJECT_VERSION_PATCH' CMakeCache.txt | grep -E -o '[[:digit:]]+$')
version="v$majorvers-$minorvers-$patchvers"
dotversion="v$majorvers.$minorvers.$patchvers"

for lang in "en-US" "zh-CN"; do
  cmake -DLOCALE=$lang .

  # flip all supported flags to true
  sed -i -E "s/\/\* #undef (.+_SUPPORTED) \*\//#define \1 1/" include/stumpless/config.h

  # build the doxygen docs
  make docs
  make docs-cpp

  # add jekyll headers to the C index files
  mv docs/$lang/html/index.html docs/$lang/html/index.html.bak
  printf -- "---\n" > docs/$lang/html/index.html
  printf -- "title: C Documentation\n" >> docs/$lang/html/index.html
  printf -- "description: \"Documentation for the Stumpless C library release $dotversion.\"\n" >> docs/$lang/html/index.html
  printf -- "tags: \"stumpless logging library c documentation\"\n" >> docs/$lang/html/index.html
  printf -- "permalink: docs/c/$version/$lang/index.html\n" >> docs/$lang/html/index.html
  printf -- "locale: $lang\n" >> docs/$lang/html/index.html
  printf -- "redirect_from:\n" >> docs/$lang/html/index.html
  printf -- "  - docs/c/latest/$lang/\n" >> docs/$lang/html/index.html
  printf -- "  - docs/c/v$majorvers/$lang/\n" >> docs/$lang/html/index.html
  printf -- "  - docs/c/v$majorvers-$minorvers/$lang/\n" >> docs/$lang/html/index.html
  if [ "$lang" = "en-US" ]; then
    printf -- "  - docs/c/latest/\n" >> docs/$lang/html/index.html
    printf -- "  - docs/c/v$majorvers/\n" >> docs/$lang/html/index.html
    printf -- "  - docs/c/v$majorvers-$minorvers/\n" >> docs/$lang/html/index.html
  fi
  printf -- "---\n" >> docs/$lang/html/index.html
  cat docs/$lang/html/index.html.bak >> docs/$lang/html/index.html
  rm docs/$lang/html/index.html.bak

  # add jekyll headers to the C++ index files
  mv docs/$lang/cpp/html/index.html docs/$lang/cpp/html/index.html.bak
  printf -- "---\n" > docs/$lang/cpp/html/index.html
  printf -- "title: C++ Documentation\n" >> docs/$lang/cpp/html/index.html
  printf -- "tags: \"stumpless logging library cpp documentation\"\n" >> docs/$lang/cpp/html/index.html
  printf -- "description: \"Documentation for the Stumpless C++ library release $dotversion.\"\n" >> docs/$lang/cpp/html/index.html
  printf -- "permalink: docs/cpp/$version/$lang/index.html\n" >> docs/$lang/cpp/html/index.html
  printf -- "redirect_from:\n" >> docs/$lang/cpp/html/index.html
  printf -- "  - docs/cpp/latest/$lang/\n" >> docs/$lang/cpp/html/index.html
  printf -- "  - docs/cpp/v$majorvers/$lang/\n" >> docs/$lang/cpp/html/index.html
  printf -- "  - docs/cpp/v$majorvers-$minorvers/$lang/\n" >> docs/$lang/cpp/html/index.html
  if [ "$lang" = "en-US" ]; then
    printf -- "  - docs/cpp/latest/\n" >> docs/$lang/cpp/html/index.html
    printf -- "  - docs/cpp/v$majorvers/\n" >> docs/$lang/cpp/html/index.html
    printf -- "  - docs/cpp/v$majorvers-$minorvers/\n" >> docs/$lang/cpp/html/index.html
  fi
  printf -- "---\n" >> docs/$lang/cpp/html/index.html
  cat docs/$lang/cpp/html/index.html.bak >> docs/$lang/cpp/html/index.html
  rm docs/$lang/cpp/html/index.html.bak

  # copy the logo and name into the assets folder
  cp -r $sourcedir/assets/ docs/$lang/html/
  cp -r $sourcedir/assets/ docs/$lang/cpp/html/
done
