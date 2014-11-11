#ifndef __STUMPLESS_TYPE_DEFINITION_H
#define __STUMPLESS_TYPE_DEFINITION_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/config.h>
#include <stumpless/type/declaration.h>

#ifdef __STUMPLESS_HAVE_TIME_H
#include <time.h>
#endif

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

/**
 * Allows for the addition of information to a Reocrd before it is logged. This
 * information may be anything from contextual information to the results of a
 * function call on the Record.
 */
struct Adapter {
  Record *( *adapt )( const Adapter *, Record * ); /**< the adapter function */
  FilterList *filters; /**< a list of filters to run each Record through
                           before the adapter is applied */
  const char *name; /**< the unique name of the Adapter */
  Dictionary *options; /**< a set of options that may customize the Adapter */
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
  short ( *compare )( const Comparator *, const void *, const void * );
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

/**
 * An event that can be logged.
 * @todo add format string for messages
 */
struct Event {
  const char *name; /**< the unique name of the Event */
  Level *level; /**< the Level of the Event */
  Dictionary *attributes; /**< the attributes describing the Event */
};

/**
 * An attribute that provides information about an Event.
 */
struct EventAttribute {
  const char *name; /**< the unique name of the EventAttribute */
  Value *default_value; /**< the default Value the attribute will assume */
};

struct FileConfiguration {
  FILE *current_file;
};

struct Filter {
  unsigned short ( *accept_record )( const Filter *, const Record * );
  unsigned short ( *accept_output )( const Filter *, const Output * );
  unsigned short ( *accept_value )( const Filter *, const Value * );
  const char *name;
  Dictionary *options;
};

/**
 * Creates an Output for a Record in a specific format.
 */
struct Formatter {
  FilterList *filters; /**< filters to apply before formatting a Record */
  Output *( *format )( const Formatter *, const Record * ); 
  const char *name; /**< the unique name of the Formatter */
  Dictionary *options; /**< options to customize behavior */
};

struct Handler {
  FilterList *filters;
  Status *( *handle )( const Handler *, const Output * );
  const char *name;
  Dictionary *options;
};

struct HTTPConfiguration {
  HTTPMethod method;
};

/**
 * The severity level of an Event.
 */
struct Level {
  const char *name; /**< the unique name of the level */
  unsigned primary; /**< the primary numerical level */
  unsigned secondary; /**<the secondary numerical level */
  unsigned tertiary; /**< the tertiary numerical level */
};

struct Log {
  //Tree *records;
  unsigned placeholder; //todo delete when tree is fixed up
};

/**
 * A collection of logging targets and configuration parameters through which
 * logging can be accomplished.
 */
struct Logger {
  AdapterList *adapters; /**< the Adapters to use on logged elements */
  Event *default_event; /**< the Event to assign Records by default */
  const char *name; /**< the unique name of the Logger */
  TargetList *targets; /**< the Targets to send logs to */
#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
  // todo consider changing this mechanism to unix sockets
  int receive_pipe; /**< the pipe used to receive messages */
  int send_pipe; /**< the pipe used to send messages */
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

/**
 * A specific instance of an Event.
 */
struct Record {
  const Event *event; /**< the event describing the record */
  Dictionary *attributes; /**< the values defining the instance */
#ifdef __STUMPLESS_HAVE_TIME_H
  time_t time; /**< the time that the event happened */
#endif
};

struct RecordAttribute {
  const EventAttribute *event_attribute;
  const char *name;
  Value *value;
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
  short ( *compare )( const Value *, const Value *, Dictionary * ); // todo move to comparator?
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
