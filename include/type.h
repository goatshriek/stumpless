#ifndef STUMPLESS_TYPE_H
#define STUMPLESS_TYPE_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum StumplessHTTPMethod;
enum StumplessSortingMethod;
enum StumplessStatusCode;

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
struct StumplessHTTConfiguration;
struct StumplessLevel;
struct StumplessLoggingProfile;
struct StumplessOutputProfile;
struct StumplessSortingConfiguration;
struct StumplessStringConfiguration;
struct StumplessThreadingConfiguration;
union StumplessType;
struct StumplessValue;
struct StumplessValueList;
struct StumplessValueListNode;
struct StumplessValueProfile;


typedef enum StumplessHTTPMethod StumplessHTTPMethod;
typedef enum StumplessSortingMethod StumplessSortingMethod;
typedef enum StumplessStatusCode StumplessStatusCode;

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
typedef struct StumplessHTTPConfiguration StumplessHTTPConfiguration;
typedef struct StumplessLevel StumplessLevel;
typedef struct StumplessLoggingProfile StumplessLoggingProfile;
typedef struct StumplessOutputProfile StumplessOutputProfile;
typedef struct StumplessSortingConfiguration StumplessSortingConfiguration;
typedef struct StumplessStringConfiguration StumplessStringConfiguration;
typedef struct StumplessThreadingConfiguration StumplessThreadingConfiguration;
typedef union StumplessType StumplessType;
typedef struct StumplessValue StumplessValue;
typedef struct StumplessValueList StumplessValueList;
typedef struct StumplessValueListNode StumplessValueListNode;
typedef struct StumplessValueProfile StumplessValueProfile;


typedef unsigned char StumplessByte;

enum StumplessHTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
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
  STUMPLESS_STRING_WRITE_FAILURE,
  STUMPLESS_MALFORMED_STRUCTURE,
  STUMPLESS_INCORRECT_INTERNAL_STATE
};

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
  unsigned logging_profile_count;
  StumplessLoggingProfile ** logging_profiles;
  unsigned output_profile_count;
  StumplessOutputProfile ** output_profiles;
  StumplessSortingConfiguration * sorting;
  StumplessStringConfiguration * string;
  StumplessThreadingConfiguration * threading;
  unsigned value_profile_count;
  StumplessValueProfile ** value_profiles;
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
  StumplessType * data;
  StumplessOutputProfile * profile;
};

struct StumplessHTTPConfiguration {
  StumplessHTTPMethod method;
};

struct StumplessLevel {
  unsigned value;
  const char * name;
};

struct StumplessLoggingProfile {
  const char * name;
  StumplessStatusCode ( *output_function )( StumplessFormattedOutput * );
};

struct StumplessOutputProfile {
  StumplessStatusCode ( *into_buffer )( StumplessFormattedOutput * );
  StumplessStatusCode ( *into_http )( StumplessFormattedOutput * );
  StumplessStatusCode ( *into_mysql )( StumplessFormattedOutput * );
  StumplessStatusCode ( *into_stream )( StumplessFormattedOutput * );
  StumplessStatusCode ( *into_string )( StumplessFormattedOutput * );
  StumplessStatusCode ( *into_tcp )( StumplessFormattedOutput * );
  unsigned short ( *is_empty )( StumplessFormattedOutput * );
  const char * name;
  char * ( *to_string )( StumplessFormattedOutput * );
};

struct StumplessSortingConfiguration {
  StumplessSortingMethod entry_method;
  StumplessSortingMethod log_method;
  unsigned short ascending;
};

struct StumplessStringConfiguration {
  size_t buffer_size;
};

struct StumplessThreadingConfiguration {
  unsigned short enabled;
};

union StumplessType {
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
  const void * v_p;
};

struct StumplessValue {
  StumplessType * data;
  const char * format;
  unsigned length;
  StumplessValueProfile * profile;
};

struct StumplessValueList {
  StumplessValueListNode * first;
  StumplessValueListNode * last;
};

struct StumplessValueListNode {
  StumplessValue * value;
  StumplessValueListNode * next;
};

struct StumplessValueProfile {
  StumplessStatusCode ( *into_string )( char *, StumplessValue * );
  const char * name;
  StumplessFormattedOutput * ( *to_binary )( StumplessValue * );
  StumplessFormattedOutput * ( *to_csv )( StumplessValue * );
  StumplessFormattedOutput * ( *to_json )( StumplessValue * );
  char * ( *to_string )( StumplessValue * );
  StumplessFormattedOutput * ( *to_text )( StumplessValue * );
  StumplessValueList * ( *to_value_list )( StumplessValue * );
  StumplessFormattedOutput * ( *to_xml )( StumplessValue * );
};

#endif
