#ifndef STUMPLESS_TYPES_H
#define STUMPLESS_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum StumplessStatusCode {
  STUMPLESS_SUCCESS = EXIT_SUCCESS,
  STUMPLESS_FAILURE,
  STUMPLESS_FILE_FAILURE,
  STUMPLESS_FILE_READ_FAILURE,
  STUMPLESS_FILE_WRITE_FAILURE,
  STUMPLESS_FILE_OPEN_FAILURE,
  STUMPLESS_FILE_CLOSE_FAILURE,
  STUMPLESS_INCORRECT_FILE_SIGNATURE,
  STUMPLESS_MEMORY_ALLOCATION_FAILURE,
  STUMPLESS_PARSE_FAILURE
} StumplessStatusCode;

typedef struct {
  unsigned value;
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
  const char * name;
  StumplessEventAttributeType type;
  const char * format;
  StumplessEventAttributeValue * default_value;
} StumplessEventAttribute;

typedef struct {
  StumplessEventAttribute * event_attribute;
  StumplessEventAttributeValue * value;
} StumplessEntryAttribute;

typedef struct {
  const char * name;
  StumplessLevel * level;
  StumplessEventAttribute ** attributes;
  unsigned attribute_count;
} StumplessEvent;

typedef struct {
  const char * description;
  StumplessEvent * event;
  StumplessEntryAttribute ** entry_attributes;
} StumplessEntry;

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
  STUMPLESS_STRING_MODE,
  STUMPLESS_TCP_MODE
} StumplessOutputMode;

typedef enum StumplessSortingMethod {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
} StumplessSortingMethod;

typedef enum StumplessHTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
} StumplessHTTPMethod;

typedef struct {
  FILE * current_file;
} StumplessFileConfiguration;

typedef struct {
  StumplessHTTPMethod method;
} StumplessHTTPConfiguration;

typedef struct {
  unsigned short enable_multithreading;
} StumplessMultithreadingConfiguration;

typedef struct {
  StumplessSortingMethod entry_method;
  StumplessSortingMethod log_method;
  unsigned short ascending;
  // function for custom entry sorting
  // function for custom log sorting
} StumplessSortingConfiguration;

typedef struct {
  StumplessFileConfiguration * file;
  StumplessHTTPConfiguration * http;
  StumplessMultithreadingConfiguration * multithreading;
  StumplessSortingConfiguration * sorting;
} StumplessConfiguration;

#endif
