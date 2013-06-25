#ifndef STUMPLESS_TYPE_H
#define STUMPLESS_TYPE_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <public_name.h>

enum __NAME( HTTPMethod );
enum __NAME( SortingMethod );
enum __NAME( StatusCode );

struct __NAME( Boolean );
struct __NAME( BooleanFormat );
struct __NAME( ByteList );
struct __NAME( Configuration );
struct __NAME( Entry );
struct __NAME( EntryAttribute );
struct __NAME( Event );
struct __NAME( EventAttribute );
struct __NAME( FileConfiguration );
struct __NAME( FormattedOutput );
struct __NAME( HTTConfiguration );
struct __NAME( Level );
struct __NAME( LoggingProfile );
struct __NAME( OutputProfile );
struct __NAME( Status );
struct __NAME( SortingConfiguration );
struct __NAME( StringConfiguration );
struct __NAME( ThreadingConfiguration );
union __NAME( Type );
struct __NAME( Value );
struct __NAME( ValueList );
struct __NAME( ValueListNode );
struct __NAME( ValueProfile );


typedef enum __NAME( HTTPMethod ) __NAME( HTTPMethod );
typedef enum __NAME( SortingMethod ) __NAME( SortingMethod );
typedef enum __NAME( StatusCode ) __NAME( StatusCode );

typedef struct __NAME( Boolean ) __NAME( Boolean );
typedef struct __NAME( BooleanFormat ) __NAME( BooleanFormat );
typedef struct __NAME( ByteList ) __NAME( ByteList );
typedef struct __NAME( Configuration ) __NAME( Configuration );
typedef struct __NAME( Entry ) __NAME( Entry );
typedef struct __NAME( EntryAttribute ) __NAME( EntryAttribute );
typedef struct __NAME( Event ) __NAME( Event );
typedef struct __NAME( EventAttribute ) __NAME( EventAttribute );
typedef struct __NAME( FileConfiguration ) __NAME( FileConfiguration );
typedef struct __NAME( FormattedOutput ) __NAME( FormattedOutput );
typedef struct __NAME( HTTPConfiguration ) __NAME( HTTPConfiguration );
typedef struct __NAME( Level ) __NAME( Level );
typedef struct __NAME( LoggingProfile ) __NAME( LoggingProfile );
typedef struct __NAME( OutputProfile ) __NAME( OutputProfile );
typedef struct __NAME( Status ) __NAME( Status );
typedef struct __NAME( SortingConfiguration ) __NAME( SortingConfiguration );
typedef struct __NAME( StringConfiguration ) __NAME( StringConfiguration );
typedef struct __NAME( ThreadingConfiguration )
               __NAME( ThreadingConfiguration );
typedef union __NAME( Type ) __NAME( Type );
typedef struct __NAME( Value ) __NAME( Value );
typedef struct __NAME( ValueList ) __NAME( ValueList );
typedef struct __NAME( ValueListNode ) __NAME( ValueListNode );
typedef struct __NAME( ValueProfile ) __NAME( ValueProfile );


typedef unsigned char __NAME( Byte );

enum __NAME( HTTPMethod ) {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
};

enum __NAME( SortingMethod ) {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
};

enum __NAME( StatusCode ) {
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

struct __NAME( Boolean ) {
  short value;
  __NAME( BooleanFormat ) * format;
};

struct __NAME( BooleanFormat ) {
  const char * true_description;
  const char * false_description;
};

struct __NAME( ByteList ) {
  __NAME( Byte ) * bytes;
  unsigned byte_count;
};

struct __NAME( Configuration ) {
  __NAME( FileConfiguration ) * file;
  __NAME( HTTPConfiguration ) * http;
  unsigned logging_profile_count;
  __NAME( LoggingProfile ) ** logging_profiles;
  unsigned output_profile_count;
  __NAME( OutputProfile ) ** output_profiles;
  __NAME( SortingConfiguration ) * sorting;
  __NAME( StringConfiguration ) * string;
  __NAME( ThreadingConfiguration ) * threading;
  unsigned value_profile_count;
  __NAME( ValueProfile ) ** value_profiles;
};

struct __NAME( Entry ) {
  const char * description;
  __NAME( Event ) * event;
  __NAME( EntryAttribute ) ** attributes;
  unsigned attribute_count;
};

struct __NAME( EntryAttribute ) {
  __NAME( EventAttribute ) * event_attribute;
  __NAME( Value ) * value;
};

struct __NAME( Event ) {
  const char * name;
  __NAME( Level ) * level;
  __NAME( EventAttribute ) ** attributes;
  unsigned attribute_count;
};

struct __NAME( EventAttribute ) {
  const char * name;
  __NAME( Value ) * default_value;
};

struct __NAME( FileConfiguration ) {
  FILE * current_file;
};

struct __NAME( FormattedOutput ) {
  __NAME( Type ) * data;
  __NAME( OutputProfile ) * profile;
};

struct __NAME( HTTPConfiguration ) {
  __NAME( HTTPMethod ) method;
};

struct __NAME( Level ) {
  unsigned value;
  const char * name;
};

struct __NAME( LoggingProfile ) {
  const char * name;
  __NAME( StatusCode ) ( *output_function )( __NAME( FormattedOutput ) * );
};

struct __NAME( OutputProfile ) {
  __NAME( StatusCode ) ( *into_buffer )( __NAME( FormattedOutput ) * );
  __NAME( StatusCode ) ( *into_http )( __NAME( FormattedOutput ) * );
  __NAME( StatusCode ) ( *into_mysql )( __NAME( FormattedOutput ) * );
  __NAME( StatusCode ) ( *into_stream )( __NAME( FormattedOutput ) * );
  __NAME( StatusCode ) ( *into_string )( __NAME( FormattedOutput ) * );
  __NAME( StatusCode ) ( *into_tcp )( __NAME( FormattedOutput ) * );
  unsigned short ( *is_empty )( __NAME( FormattedOutput ) * );
  const char * name;
  char * ( *to_string )( __NAME( FormattedOutput ) * );
};

struct __NAME( Status ) {
  unsigned short error : 1;
  unsigned short failure : 1;
  const char * description;
  const char * name;
};

struct __NAME( SortingConfiguration ) {
  __NAME( SortingMethod ) entry_method;
  __NAME( SortingMethod ) log_method;
  unsigned short ascending;
};

struct __NAME( StringConfiguration ) {
  size_t buffer_size;
};

struct __NAME( ThreadingConfiguration ) {
  unsigned short enabled;
};

union __NAME( Type ) {
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

struct __NAME( Value ) {
  __NAME( Type ) * data;
  const char * format;
  unsigned length;
  __NAME( ValueProfile ) * profile;
};

struct __NAME( ValueList ) {
  __NAME( ValueListNode ) * first;
  __NAME( ValueListNode ) * last;
};

struct __NAME( ValueListNode ) {
  __NAME( Value ) * value;
  __NAME( ValueListNode ) * next;
};

struct __NAME( ValueProfile ) {
  __NAME( StatusCode ) ( *into_string )( char *, __NAME( Value ) * );
  const char * name;
  __NAME( FormattedOutput ) * ( *to_binary )( __NAME( Value ) * );
  __NAME( FormattedOutput ) * ( *to_csv )( __NAME( Value ) * );
  __NAME( FormattedOutput ) * ( *to_json )( __NAME( Value ) * );
  char * ( *to_string )( __NAME( Value ) * );
  __NAME( FormattedOutput ) * ( *to_text )( __NAME( Value ) * );
  __NAME( ValueList ) * ( *to_value_list )( __NAME( Value ) * );
  __NAME( FormattedOutput ) * ( *to_xml )( __NAME( Value ) * );
};

#endif
