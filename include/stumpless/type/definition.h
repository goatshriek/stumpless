#ifndef __STUMPLESS_TYPE_DEFINITION_H
#define __STUMPLESS_TYPE_DEFINITION_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stumpless/config.h>
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
  Record *( *adapt )( Record *, Dictionary * );
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
  size_t byte_count;
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

struct Record {
  const char *description;
  Event *event;
  RecordAttributeList *attributes;
};

struct RecordAttribute {
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
  unsigned short ( *accept_record )( const Record *, Dictionary * );
  unsigned short ( *accept_output )( const Output *, Dictionary * );
  unsigned short ( *accept_value )( const Value *, Dictionary * );
  const char *name;
  Dictionary *options;
};

struct Formatter {
  FilterList *filters;
  Output *( *format )( const Record *, Dictionary * );
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
  unsigned placeholder; //todo delete when tree is fixed up
};

struct Logger {
  const char *name;
  TargetList *targets;
#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
  int receive_pipe;
  int send_pipe;
#endif
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

struct Status {
  unsigned short error : 1;
  unsigned short failure : 1;
  unsigned short warning : 1;
  const char *description;
  const char *name;
};

struct SortingConfiguration {
  SortingMethod record_method;
  SortingMethod log_method;
  unsigned short ascending;
};

struct StringConfiguration {
  size_t buffer_size;
};

struct Target {
  AdapterList *adapters;
  Formatter *formatter;
  Handler *handler;
};

struct ThreadingConfiguration {
  unsigned short enabled : 1;
};

union Type {
  unsigned short u_s;
  unsigned short *u_s_p;
  signed short s;
  signed short *s_p;
  unsigned int u_i;
  unsigned int *u_i_p;
  signed int i;
  signed int *i_p;
  unsigned long u_l;
  unsigned long *u_l_p;
  signed long l;
  signed long *l_p;
  unsigned long long u_l_l;
  unsigned long long *u_l_l_p;
  signed long long l_l;
  signed long long *l_l_p;
  char c;
  char *c_p;
  signed char s_c;
  signed char *s_c_p;
  unsigned char u_c;
  unsigned char *u_c_p;
  float f;
  float *f_p;
  double d;
  double *d_p;
  long double l_d;
  long double *l_d_p;
  void *v_p;
#ifdef __STUMPLESS_HAVE_TIME_H
  time_t time;
#endif
};

struct Value {
  Type *data;
  const char *format;
  size_t length;
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
