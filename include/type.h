#ifndef STUMPLESS_TYPE_H
#define STUMPLESS_TYPE_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum StumplessHTTPMethod;
enum StumplessOutputFormat;
enum StumplessOutputMode;
enum StumplessSortingMethod;
enum StumplessStatusCode;
enum StumplessValueType; // todo remove

struct StumplessBoolean;
struct StumplessBooleanFormat;
struct StumplessByteList;
struct StumplessConfiguration;
struct StumplessEntry;
struct StumplessEntryAttribute;
struct StumplessEvent;
struct StumplessEventAttribute;
struct StumplessFileConfiguration;
struct StumplessFormattedOutput;
union StumplessFormattedPayload;
struct StumplessHTTConfiguration;
struct StumplessLevel;
struct StumplessMultithreadingConfiguration;
struct StumplessSortingConfiguration;
struct StumplessStringConfiguration;
struct StumplessTypeProfile;
struct StumplessValue;
union StumplessValueData;
struct StumplessValueList;
struct StumplessValueListNode;


typedef enum StumplessHTTPMethod StumplessHTTPMethod;
typedef enum StumplessOutputFormat StumplessOutputFormat;
typedef enum StumplessOutputMode StumplessOutputMode;
typedef enum StumplessSortingMethod StumplessSortingMethod;
typedef enum StumplessStatusCode StumplessStatusCode;
typedef enum StumplessValueType StumplessValueType; // todo remove

typedef struct StumplessBoolean StumplessBoolean;
typedef struct StumplessBooleanFormat StumplessBooleanFormat;
typedef struct StumplessByteList StumplessByteList;
typedef struct StumplessConfiguration StumplessConfiguration;
typedef struct StumplessEntry StumplessEntry;
typedef struct StumplessEntryAttribute StumplessEntryAttribute;
typedef struct StumplessEvent StumplessEvent;
typedef struct StumplessEventAttribute StumplessEventAttribute;
typedef struct StumplessFileConfiguration StumplessFileConfiguration;
typedef struct StumplessFormattedOutput StumplessFormattedOutput;
typedef union StumplessFormattedPayload StumplessFormattedPayload;
typedef struct StumplessHTTPConfiguration StumplessHTTPConfiguration;
typedef struct StumplessLevel StumplessLevel;
typedef struct StumplessMultithreadingConfiguration
        StumplessMultithreadingConfiguration;
typedef struct StumplessSortingConfiguration StumplessSortingConfiguration;
typedef struct StumplessStringConfiguration StumplessStringConfiguration;
typedef struct StumplessTypeProfile StumplessTypeProfile;
typedef struct StumplessValue StumplessValue;
typedef union StumplessValueData StumplessValueData;
typedef struct StumplessValueList StumplessValueList;
typedef struct StumplessValueListNode StumplessValueListNode;


typedef unsigned char StumplessByte;

enum StumplessHTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
};

enum StumplessOutputFormat {
  STUMPLESS_BINARY,
  STUMPLESS_CSV,
  STUMPLESS_JSON,
  STUMPLESS_TEXT,
  STUMPLESS_XML
};

enum StumplessOutputMode {
  STUMPLESS_FILE_MODE,
  STUMPLESS_HTTP_MODE,
  STUMPLESS_MYSQL_MODE,
  STUMPLESS_STRING_MODE,
  STUMPLESS_TCP_MODE
};

enum StumplessSortingMethod {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
};

enum StumplessStatusCode {
  STUMPLESS_SUCCESS = EXIT_SUCCESS,
  STUMPLESS_FAILURE,
  STUMPLESS_EMPTY_ARGUMENT,
  STUMPLESS_INCOMPATIBLE_ARGUMENTS,
  STUMPLESS_FILE_FAILURE,
  STUMPLESS_FILE_CLOSE_FAILURE,
  STUMPLESS_FILE_OPEN_FAILURE,
  STUMPLESS_FILE_READ_FAILURE,
  STUMPLESS_FILE_WRITE_FAILURE,
  STUMPLESS_INCORRECT_FILE_SIGNATURE,
  STUMPLESS_MEMORY_ALLOCATION_FAILURE,
  STUMPLESS_PARSE_FAILURE,
  STUMPLESS_STRING_WRITE_FAILURE
};

enum StumplessValueType {
  STUMPLESS_UNSIGNED_SHORT,
  STUMPLESS_UNSIGNED_SHORT_POINTER,
  STUMPLESS_SHORT,
  STUMPLESS_SHORT_POINTER,
  STUMPLESS_UNSIGNED_INT,
  STUMPLESS_UNSIGNED_INT_POINTER,
  STUMPLESS_INT,
  STUMPLESS_INT_POINTER,
  STUMPLESS_UNSIGNED_LONG,
  STUMPLESS_UNSIGNED_LONG_POINTER,
  STUMPLESS_LONG,
  STUMPLESS_LONG_POINTER,
  STUMPLESS_UNSIGNED_LONG_LONG,
  STUMPLESS_UNSIGNED_LONG_LONG_POINTER,
  STUMPLESS_LONG_LONG,
  STUMPLESS_LONG_LONG_POINTER,
  STUMPLESS_CHAR,
  STUMPLESS_CHAR_POINTER,
  STUMPLESS_SIGNED_CHAR,
  STUMPLESS_SIGNED_CHAR_POINTER,
  STUMPLESS_UNSIGNED_CHAR,
  STUMPLESS_UNSIGNED_CHAR_POINTER,
  STUMPLESS_FLOAT,
  STUMPLESS_FLOAT_POINTER,
  STUMPLESS_DOUBLE,
  STUMPLESS_DOUBLE_POINTER,
  STUMPLESS_LONG_DOUBLE,
  STUMPLESS_LONG_DOUBLE_POINTER,
  STUMPLESS_STRING,
  STUMPLESS_STRING_POINTER,
  STUMPLESS_VOID_POINTER,
  STUMPLESS_BOOLEAN,
  STUMPLESS_CUSTOM_DATA
}; // todo remove


struct StumplessBoolean {
  short value;
  StumplessBooleanFormat * format;
};

struct StumplessBooleanFormat {
  const char * true_description;
  const char * false_description;
};

struct StumplessByteList {
  StumplessByte * bytes;
  unsigned byte_count;
};

struct StumplessConfiguration {
  StumplessFileConfiguration * file;
  StumplessHTTPConfiguration * http;
  StumplessMultithreadingConfiguration * multithreading;
  StumplessSortingConfiguration * sorting;
  StumplessStringConfiguration * string;
  StumplessTypeProfile ** profiles;
  unsigned profile_count;
};

struct StumplessEntry {
  const char * description;
  StumplessEvent * event;
  StumplessEntryAttribute ** attributes;
  unsigned attribute_count;
};

struct StumplessEntryAttribute {
  StumplessEventAttribute * event_attribute;
  StumplessValue * value;
};

struct StumplessEvent {
  const char * name;
  StumplessLevel * level;
  StumplessEventAttribute ** attributes;
  unsigned attribute_count;
};

struct StumplessEventAttribute {
  const char * name;
  StumplessValue * default_value;
};

struct StumplessFileConfiguration {
  FILE * current_file;
};

struct StumplessFormattedOutput {
  StumplessOutputFormat format;
  StumplessFormattedPayload * payload;
};

union StumplessFormattedPayload {
  StumplessByteList * bytes;
  StumplessValueList * values;
};

struct StumplessHTTPConfiguration {
  StumplessHTTPMethod method;
};

struct StumplessLevel {
  unsigned value;
  const char * name;
};

struct StumplessMultithreadingConfiguration {
  unsigned short enabled;
};

struct StumplessSortingConfiguration {
  StumplessSortingMethod entry_method;
  StumplessSortingMethod log_method;
  unsigned short ascending;
};

struct StumplessStringConfiguration {
  size_t buffer_size;
};

struct StumplessTypeProfile {
  const char * name;
  StumplessFormattedOutput * ( *to_binary )( StumplessValue * );
  StumplessFormattedOutput * ( *to_csv )( StumplessValue * );
  StumplessFormattedOutput * ( *to_json )( StumplessValue * );
  char * ( *to_string )( StumplessValue * );
  StumplessFormattedOutput * ( *to_text )( StumplessValue * );
  StumplessValueList * ( *to_value_list )( StumplessValue * );
  StumplessFormattedOutput * ( *to_xml )( StumplessValue * );
};

struct StumplessValue {
  const char * format;
  StumplessValueType type; // todo remove
  StumplessValueData * data;
  unsigned length;
  StumplessTypeProfile * profile;
};

union StumplessValueData {
  unsigned short u_s;
  const unsigned short * u_s_p;
  signed short s;
  const signed short * s_p;
  unsigned int u_i;
  const unsigned int * u_i_p;
  signed int i;
  const signed int * i_p;
  unsigned long u_l;
  const unsigned long * u_l_p;
  signed long l;
  const signed long * l_p;
  unsigned long long u_l_l;
  const unsigned long long * u_l_l_p;
  signed long long l_l;
  const signed long long * l_l_p;
  char c;
  const char * c_p;
  signed char s_c;
  const signed char * s_c_p;
  unsigned char u_c;
  const unsigned char * u_c_p;
  float f;
  const float * f_p;
  double d;
  const double * d_p;
  long double l_d;
  const long double * l_d_p;
  const char ** str_p;
  const void * v_p;
  StumplessBoolean * boolean; // todo remove
};

struct StumplessValueList {
  StumplessValueListNode * first;
  StumplessValueListNode * last;
};

struct StumplessValueListNode {
  StumplessValue * value;
  StumplessValueListNode * next;
};

#endif
