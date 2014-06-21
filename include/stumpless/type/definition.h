#ifndef __STUMPLESS_TYPE_DEFINITION_H
#define __STUMPLESS_TYPE_DEFINITION_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stumpless/type/declaration.h>

typedef unsigned char Byte;

enum HTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
};

enum SortingMethod {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
};

struct Adapter {
  Entry *( *adapt )( Value *, Dictionary * );
  FilterList *filters;
  const char *name;
  Dictionary *options;
};

struct Boolean {
  short value;
  BooleanFormat *format;
};

struct BooleanFormat {
  const char *true_description;
  const char *false_description;
};

struct ByteList {
  Byte *bytes;
  unsigned byte_count;
};

struct Comparator {
  short ( *compare )( const void *, const void *, Dictionary * );
  const char *name;
  Dictionary *options;
};

struct Configuration {
  FileConfiguration *default_file;
  HTTPConfiguration *default_http;
  SortingConfiguration *sorting;
  StringConfiguration *string;
  ThreadingConfiguration *threading;
};

struct Entry {
  const char *description;
  Event *event;
  EntryAttributeList *attributes;
};

struct EntryAttribute {
  const EventAttribute *event_attribute;
  Value *value;
};

struct Event {
  const char *name;
  Level *level;
  EventAttributeList *attributes;
};

struct EventAttribute {
  const char *name;
  Value *default_value;
};

struct FileConfiguration {
  FILE *current_file;
};

struct Filter {
  unsigned short ( *accept_entry )( const Entry *, Dictionary * );
  unsigned short ( *accept_output )( const Output *, Dictionary * );
  unsigned short ( *accept_value )( const Value *, Dictionary * );
  const char *name;
  Dictionary *options;
};

struct Formatter {
  FilterList *filters;
  Output *( *format )( const Entry *, Dictionary * );
  HandlerList *handlers;
  const char *name;
  Dictionary *options;
};

struct Handler {
  FilterList *filters;
  Status *( *handle )( const Output *, Dictionary * );
  const char *name;
  Dictionary *options;
};

struct HTTPConfiguration {
  HTTPMethod method;
};

struct Level {
  unsigned value;
  const char *name;
};

struct Log {
  //Tree *records;
  unsigned placeholder; //delete when tree is fixed up
};

struct Logger {
  AdapterList *adapters;
  const char *name;
  FormatterList *formatters;
};

struct Output {
  Type *data;
  OutputProfile *profile;
};

struct OutputProfile {
  Status *( *into_buffer )( const Output * );
  Status *( *into_http )( const Output * );
  Status *( *into_mysql )( const Output * );
  Status *( *into_stream )( const Output *, FILE * );
  Status *( *into_string )( const Output * );
  Status *( *into_tcp )( const Output * );
  unsigned short ( *is_empty )( const Output * );
  const char *name;
  char *( *to_string )( const Output * );
};

struct Record {
  time_t time;
  Dictionary *attributes;
};

struct Status {
  unsigned short error : 1;
  unsigned short failure : 1;
  unsigned short warning : 1;
  const char *description;
  const char *name;
};

struct SortingConfiguration {
  SortingMethod entry_method;
  SortingMethod log_method;
  unsigned short ascending;
};

struct StringConfiguration {
  size_t buffer_size;
};

struct ThreadingConfiguration {
  unsigned short enabled : 1;
};

union Type {
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

struct Value {
  Type *data;
  const char *format;
  unsigned length;
  ValueProfile *profile;
};

struct ValueProfile {
  short ( *compare )( const Value *, const Value *, Dictionary * );
  Status *( *into_string )( char *, const Value * );
  const char * name;
  Output *( *to_binary )( const Value * );
  Output *( *to_csv )( const Value * );
  Output *( *to_json )( const Value * );
  char * ( *to_string )( const Value * );
  Output *( *to_text )( const Value * );
  ValueList *( *to_value_list )( const Value * );
  Output *( *to_xml )( const Value * );
};

#endif
