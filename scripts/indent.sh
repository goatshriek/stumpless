#!/bin/sh

indent \
  --blank-lines-before-block-comments \
  --braces-on-func-def-line \
  --braces-on-if-line \
  --braces-on-struct-decl-line \
  --case-indentation2 \
  --comment-line-length80 \
  --cuddle-else \
  --format-all-comments \
  --ignore-profile \
  --indent-level2 \
  --line-length80 \
  --no-space-after-for \
  --no-space-after-if \
  --no-space-after-function-call-names \
  --no-tabs \
  --preprocessor-indentation2 \
  --space-after-parentheses \
  --tab-size2 \
  $1
