#ifndef STUMPLESS_TYPES_H
#define STUMPLESS_TYPES_H

#include <stdio.h>
#include <time.h>

typedef struct {
  unsigned level;
  const char * name;
} StumplessLevel;

typedef enum StumplessEventAttributeType {
  STUMPLESS_UNSIGNED_SHORT,
  STUMPLESS_UNSIGNED_SHORT_POINTER,
  STUMPLESS_SIGNED_SHORT,
  STUMPLESS_SIGNED_SHORT_POINTER
} StumplessEventAttributeType;

typedef union {
  unsigned short u_s;
  unsigned short * u_s_p;
  signed short s_s;
  signed short * s_s_p;
} StumplessEventAttributeValue;

typedef struct {
  StumplessEventAttributeType type;
  StumplessEventAttributeValue * value;
  StumplessEventAttributeValue * default_value;
} StumplessEventAttribute;

typedef struct {
  unsigned id;
  const char * name;
  StumplessLevel * level;
  StumplessEventAttribute ** attributes;
  unsigned attribute_count;
} StumplessEvent;

typedef enum StumplessOutputFormat {
  STUMPLESS_CSV,
  STUMPLESS_JSON,
  STUMPLESS_TEXT,
  STUMPLESS_XML
} StumplessOutputFormat;

typedef enum StumplessOutputMode {
  STUMPLESS_FILE_MODE,
  STUMPLESS_HTTP_MODE,
  STUMPLESS_MYSQL_MODE,
  STUMPLESS_TCP_MODE
} StumplessOutputMode;

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
