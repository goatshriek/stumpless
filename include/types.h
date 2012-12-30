#ifndef STUMPLESS_TYPES_H
#define STUMPLESS_TYPES_H

#include <stdio.h>

typedef enum StumplessStatusCode {
  STUMPLESS_SUCCESS,
  STUMPLESS_FAILURE,
  STUMPLESS_FILE_FAILURE,
  STUMPLESS_FILE_READ_FAILURE,
  STUMPLESS_FILE_WRITE_FAILURE,
  STUMPLESS_FILE_OPEN_FAILURE,
  STUMPLESS_FILE_CLOSE_FAILURE,
  STUMPLESS_INCORRECT_FILE_SIGNATURE,
  STUMPLESS_MEMORY_ALLOCATION_FAILURE,
  STUMPLESS_PARSE_ERROR
} StumplessStatusCode;

typedef struct {
  FILE * current_file;
} StumplessFileConfiguration;

typedef struct {
  StumplessFileConfiguration * file;
} StumplessConfiguration;

#endif
