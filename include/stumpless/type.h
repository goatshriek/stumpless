#ifndef __STUMPLESS_TYPE_H
#define __STUMPLESS_TYPE_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stumpless/public_name.h>

enum __STUMPLESS_NAME( HTTPMethod );
enum __STUMPLESS_NAME( SortingMethod );

struct __STUMPLESS_NAME( Adapter );
struct __STUMPLESS_NAME( AdapterList );
struct __STUMPLESS_NAME( Boolean );
struct __STUMPLESS_NAME( BooleanFormat );
struct __STUMPLESS_NAME( ByteList );
struct __STUMPLESS_NAME( Configuration );
struct __STUMPLESS_NAME( Dictionary );
struct __STUMPLESS_NAME( Entry );
struct __STUMPLESS_NAME( EntryAttribute );
struct __STUMPLESS_NAME( EntryAttributeList );
struct __STUMPLESS_NAME( Event );
struct __STUMPLESS_NAME( EventAttribute );
struct __STUMPLESS_NAME( EventAttributeList );
struct __STUMPLESS_NAME( FileConfiguration );
struct __STUMPLESS_NAME( Filter );
struct __STUMPLESS_NAME( FilterList );
struct __STUMPLESS_NAME( Formatter );
struct __STUMPLESS_NAME( FormatterList );
struct __STUMPLESS_NAME( Handler );
struct __STUMPLESS_NAME( HandlerList );
struct __STUMPLESS_NAME( HTTConfiguration );
struct __STUMPLESS_NAME( Level );
struct __STUMPLESS_NAME( Log );
struct __STUMPLESS_NAME( Logger );
struct __STUMPLESS_NAME( Output );
struct __STUMPLESS_NAME( OutputProfile );
struct __STUMPLESS_NAME( Record );
struct __STUMPLESS_NAME( RecordList );
struct __STUMPLESS_NAME( Status );
struct __STUMPLESS_NAME( SortingConfiguration );
struct __STUMPLESS_NAME( StringConfiguration );
struct __STUMPLESS_NAME( ThreadingConfiguration );
union __STUMPLESS_NAME( Type );
struct __STUMPLESS_NAME( Value );
struct __STUMPLESS_NAME( ValueList );
struct __STUMPLESS_NAME( ValueProfile );


typedef enum __STUMPLESS_NAME( HTTPMethod )
        __STUMPLESS_NAME( HTTPMethod );
typedef enum __STUMPLESS_NAME( SortingMethod )
        __STUMPLESS_NAME( SortingMethod );

typedef struct __STUMPLESS_NAME( Adapter )
        __STUMPLESS_NAME( Adapter );
typedef struct __STUMPLESS_NAME( AdapterList )
        __STUMPLESS_NAME( AdapterList );
typedef struct __STUMPLESS_NAME( Boolean )
        __STUMPLESS_NAME( Boolean );
typedef struct __STUMPLESS_NAME( BooleanFormat )
        __STUMPLESS_NAME( BooleanFormat );
typedef struct __STUMPLESS_NAME( ByteList )
        __STUMPLESS_NAME( ByteList );
typedef struct __STUMPLESS_NAME( Configuration )
        __STUMPLESS_NAME( Configuration );
typedef struct __STUMPLESS_NAME( Dictionary )
        __STUMPLESS_NAME( Dictionary );
typedef struct __STUMPLESS_NAME( Entry )
        __STUMPLESS_NAME( Entry );
typedef struct __STUMPLESS_NAME( EntryAttribute )
        __STUMPLESS_NAME( EntryAttribute );
typedef struct __STUMPLESS_NAME( EntryAttributeList )
        __STUMPLESS_NAME( EntryAttributeList );
typedef struct __STUMPLESS_NAME( Event )
        __STUMPLESS_NAME( Event );
typedef struct __STUMPLESS_NAME( EventAttribute )
        __STUMPLESS_NAME( EventAttribute );
typedef struct __STUMPLESS_NAME( EventAttributeList )
        __STUMPLESS_NAME( EventAttributeList );
typedef struct __STUMPLESS_NAME( FileConfiguration )
        __STUMPLESS_NAME( FileConfiguration );
typedef struct __STUMPLESS_NAME( Filter )
        __STUMPLESS_NAME( Filter );
typedef struct __STUMPLESS_NAME( FilterList )
        __STUMPLESS_NAME( FilterList );
typedef struct __STUMPLESS_NAME( Formatter )
        __STUMPLESS_NAME( Formatter );
typedef struct __STUMPLESS_NAME( FormatterList )
        __STUMPLESS_NAME( FormatterList );
typedef struct __STUMPLESS_NAME( Handler )
        __STUMPLESS_NAME( Handler );
typedef struct __STUMPLESS_NAME( HandlerList )
        __STUMPLESS_NAME( HandlerList );
typedef struct __STUMPLESS_NAME( HTTPConfiguration )
        __STUMPLESS_NAME( HTTPConfiguration );
typedef struct __STUMPLESS_NAME( Level )
        __STUMPLESS_NAME( Level );
typedef struct __STUMPLESS_NAME( Log )
        __STUMPLESS_NAME( Log );
typedef struct __STUMPLESS_NAME( Logger )
        __STUMPLESS_NAME( Logger );
typedef struct __STUMPLESS_NAME( Output )
        __STUMPLESS_NAME( Output );
typedef struct __STUMPLESS_NAME( OutputProfile )
        __STUMPLESS_NAME( OutputProfile );
typedef struct __STUMPLESS_NAME( Record )
        __STUMPLESS_NAME( Record );
typedef struct __STUMPLESS_NAME( RecordList )
        __STUMPLESS_NAME( RecordList );
typedef struct __STUMPLESS_NAME( Status )
        __STUMPLESS_NAME( Status );
typedef struct __STUMPLESS_NAME( SortingConfiguration )
        __STUMPLESS_NAME( SortingConfiguration );
typedef struct __STUMPLESS_NAME( StringConfiguration )
        __STUMPLESS_NAME( StringConfiguration );
typedef struct __STUMPLESS_NAME( ThreadingConfiguration )
        __STUMPLESS_NAME( ThreadingConfiguration );
typedef union __STUMPLESS_NAME( Type )
        __STUMPLESS_NAME( Type );
typedef struct __STUMPLESS_NAME( Value )
        __STUMPLESS_NAME( Value );
typedef struct __STUMPLESS_NAME( ValueList )
        __STUMPLESS_NAME( ValueList );
typedef struct __STUMPLESS_NAME( ValueProfile )
        __STUMPLESS_NAME( ValueProfile );

typedef unsigned char
        __STUMPLESS_NAME( Byte );

enum __STUMPLESS_NAME( HTTPMethod ) {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
};

enum __STUMPLESS_NAME( SortingMethod ) {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
};

struct __STUMPLESS_NAME( Adapter ) {
  __STUMPLESS_NAME( Entry ) * ( *adapt )( __STUMPLESS_NAME( Value ) *, __STUMPLESS_NAME( Dictionary ) * );
  __STUMPLESS_NAME( FilterList ) * filters;
  const char * name;
  __STUMPLESS_NAME( Dictionary ) * options;
};

struct __STUMPLESS_NAME( Boolean ) {
  short value;
  __STUMPLESS_NAME( BooleanFormat ) * format;
};

struct __STUMPLESS_NAME( BooleanFormat ) {
  const char * true_description;
  const char * false_description;
};

struct __STUMPLESS_NAME( ByteList ) {
  __STUMPLESS_NAME( Byte ) * bytes;
  unsigned byte_count;
};

struct __STUMPLESS_NAME( Configuration ) {
  __STUMPLESS_NAME( FileConfiguration ) * default_file;
  __STUMPLESS_NAME( HTTPConfiguration ) * default_http;
  __STUMPLESS_NAME( SortingConfiguration ) * sorting;
  __STUMPLESS_NAME( StringConfiguration ) * string;
  __STUMPLESS_NAME( ThreadingConfiguration ) * threading;
};

struct __STUMPLESS_NAME( Entry ) {
  const char * description;
  __STUMPLESS_NAME( Event ) * event;
  __STUMPLESS_NAME( EntryAttributeList ) * attributes;
};

struct __STUMPLESS_NAME( EntryAttribute ) {
  __STUMPLESS_NAME( EventAttribute ) * event_attribute;
  __STUMPLESS_NAME( Value ) * value;
};

struct __STUMPLESS_NAME( Event ) {
  const char * name;
  __STUMPLESS_NAME( Level ) * level;
  __STUMPLESS_NAME( EventAttributeList ) * attributes;
};

struct __STUMPLESS_NAME( EventAttribute ) {
  const char * name;
  __STUMPLESS_NAME( Value ) * default_value;
};

struct __STUMPLESS_NAME( FileConfiguration ) {
  FILE * current_file;
};

struct __STUMPLESS_NAME( Filter ) {
  unsigned short ( *accept_entry )( __STUMPLESS_NAME( Entry ) *, __STUMPLESS_NAME( Dictionary ) * );
  unsigned short ( *accept_output )( __STUMPLESS_NAME( Output ) *, __STUMPLESS_NAME( Dictionary ) *);
  unsigned short ( *accept_value )( __STUMPLESS_NAME( Value ) *, __STUMPLESS_NAME( Dictionary ) * );
  const char * name;
  __STUMPLESS_NAME( Dictionary ) * options;
};

struct __STUMPLESS_NAME( Formatter ) {
  __STUMPLESS_NAME( FilterList ) * filters;
  __STUMPLESS_NAME( Output ) * ( *format )( __STUMPLESS_NAME( Entry ) *, __STUMPLESS_NAME( Dictionary ) * );
  __STUMPLESS_NAME( HandlerList ) * handlers;
  const char * name;
  __STUMPLESS_NAME( Dictionary ) * options;
};

struct __STUMPLESS_NAME( Handler ) {
  __STUMPLESS_NAME( FilterList ) * filters;
  __STUMPLESS_NAME( Status ) * ( *handle )( __STUMPLESS_NAME( Output ) *, __STUMPLESS_NAME( Dictionary ) * );
  const char * name;
  __STUMPLESS_NAME( Dictionary ) * options;
};

struct __STUMPLESS_NAME( HTTPConfiguration ) {
  __STUMPLESS_NAME( HTTPMethod ) method;
};

struct __STUMPLESS_NAME( Level ) {
  unsigned value;
  const char * name;
};

struct __STUMPLESS_NAME( Log ) {
  // todo list of records
  unsigned short placeholder;
};

struct __STUMPLESS_NAME( Logger ) {
  __STUMPLESS_NAME( AdapterList ) * adapters;
  const char * name;
  __STUMPLESS_NAME( FormatterList ) * formatters;
};

struct __STUMPLESS_NAME( Output ) {
  __STUMPLESS_NAME( Type ) * data;
  __STUMPLESS_NAME( OutputProfile ) * profile;
};

struct __STUMPLESS_NAME( OutputProfile ) {
  __STUMPLESS_NAME( Status ) * ( *into_buffer )( __STUMPLESS_NAME( Output ) * );
  __STUMPLESS_NAME( Status ) * ( *into_http )( __STUMPLESS_NAME( Output ) * );
  __STUMPLESS_NAME( Status ) * ( *into_mysql )( __STUMPLESS_NAME( Output ) * );
  __STUMPLESS_NAME( Status ) * ( *into_stream )( __STUMPLESS_NAME( Output ) *, FILE * );
  __STUMPLESS_NAME( Status ) * ( *into_string )( __STUMPLESS_NAME( Output ) * );
  __STUMPLESS_NAME( Status ) * ( *into_tcp )( __STUMPLESS_NAME( Output ) * );
  unsigned short ( *is_empty )( __STUMPLESS_NAME( Output ) * );
  const char * name;
  char * ( *to_string )( __STUMPLESS_NAME( Output ) * );
};

struct __STUMPLESS_NAME( Record ) {
  time_t time;
  __STUMPLESS_NAME( Dictionary ) * attributes;
};

struct __STUMPLESS_NAME( Status ) {
  unsigned short error : 1;
  unsigned short failure : 1;
  unsigned short warning : 1;
  const char * description;
  const char * name;
};

struct __STUMPLESS_NAME( SortingConfiguration ) {
  __STUMPLESS_NAME( SortingMethod ) entry_method;
  __STUMPLESS_NAME( SortingMethod ) log_method;
  unsigned short ascending;
};

struct __STUMPLESS_NAME( StringConfiguration ) {
  size_t buffer_size;
};

struct __STUMPLESS_NAME( ThreadingConfiguration ) {
  unsigned short enabled : 1;
};

union __STUMPLESS_NAME( Type ) {
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

struct __STUMPLESS_NAME( Value ) {
  __STUMPLESS_NAME( Type ) * data;
  const char * format;
  unsigned length;
  __STUMPLESS_NAME( ValueProfile ) * profile;
};

struct __STUMPLESS_NAME( ValueProfile ) {
  short ( *compare )( const __STUMPLESS_NAME( Value ) *, const __STUMPLESS_NAME( Value ) *, __STUMPLESS_NAME( Dictionary ) * );
  __STUMPLESS_NAME( Status ) * ( *into_string )( char *, __STUMPLESS_NAME( Value ) * );
  const char * name;
  __STUMPLESS_NAME( Output ) * ( *to_binary )( __STUMPLESS_NAME( Value ) * );
  __STUMPLESS_NAME( Output ) * ( *to_csv )( __STUMPLESS_NAME( Value ) * );
  __STUMPLESS_NAME( Output ) * ( *to_json )( __STUMPLESS_NAME( Value ) * );
  char * ( *to_string )( __STUMPLESS_NAME( Value ) * );
  __STUMPLESS_NAME( Output ) * ( *to_text )( __STUMPLESS_NAME( Value ) * );
  __STUMPLESS_NAME( ValueList ) * ( *to_value_list )( __STUMPLESS_NAME( Value ) * );
  __STUMPLESS_NAME( Output ) * ( *to_xml )( __STUMPLESS_NAME( Value ) * );
};

#endif
