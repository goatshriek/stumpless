#!/bin/bash

for filename in `find $1 | egrep '\.c'`;
do
  gcov -n -o . $filename;
done
