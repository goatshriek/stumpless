#ifndef STUMPLESS_TYPES_H
#define STUMPLESS_TYPES_H

#include <stdio.h>

typedef struct {
  FILE * current_file;
} StumplessFileConfiguration;

typedef struct {
  StumplessFileConfiguration * file;
} StumplessConfiguration;

#endif
