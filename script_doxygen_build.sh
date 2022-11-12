# assumes that you are in a build folder that has already been configured
# with cmake, including c++ support

# flip all supported flags to true
sed -i -E "s/\/\* #undef (.+_SUPPORTED) \*\//#define \1 1/" include/stumpless/config.h

# build the doxygen docs
make docs
make docs-cpp

# replace the markdown tags with html entities
sed -i -E "s/:brazil:/\&#127463;\&#127479;/g" docs/html/index.html
sed -i -E "s/:bulgaria:/\&#127463;\&#127468;/g" docs/html/index.html
sed -i -E "s/:cn:/\&#127464;\&#127475;/g" docs/html/index.html
sed -i -E "s/:czech_republic:/\&#127464;\&#127487;/g" docs/html/index.html
sed -i -E "s/:de:/\&#127465;\&#127466;/g" docs/html/index.html
sed -i -E "s/:es:/\&#127466;\&#127480;/g" docs/html/index.html
sed -i -E "s/:fr:/\&#127467;\&#127479;/g" docs/html/index.html
sed -i -E "s/:greece:/\&#127468;\&#127479;/g" docs/html/index.html
sed -i -E "s/:india:/\&#127470;\&#127475;/g" docs/html/index.html
sed -i -E "s/:it:/\&#127470;\&#127481;/g" docs/html/index.html
sed -i -E "s/:poland:/\&#127477;\&#127473;/g" docs/html/index.html
sed -i -E "s/:slovakia:/\&#127480;\&#127472;/g" docs/html/index.html
sed -i -E "s/:sweden:/\&#127480;\&#127466;/g" docs/html/index.html
sed -i -E "s/:us:/\&#127482;\&#127480;/g" docs/html/index.html

# add jekyll header to the index file
mv docs/html/index.html docs/html/index.html.bak
printf -- "---\ntitle: C Documentation\nkeywords: stumpless, logging, library, c, doxygen\nlast_updated: " > docs/html/index.html
date "+%B %e, %Y" >> docs/html/index.html
printf "summary: \"Documentation for the latest version of Stumpless.\"\npermalink: docs/c/latest/index.html\n---\n" >> docs/html/index.html
cat docs/html/index.html.bak >> docs/html/index.html
rm docs/html/index.html.bak

# copy the logo and name into the assets folder
sourcedir=$(grep -E '.*_SOURCE_DIR:STATIC=.*' CMakeCache.txt | grep -E -o '/.*')
cp -r $sourcedir/assets/ docs/html/
