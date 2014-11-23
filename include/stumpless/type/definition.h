#ifndef __STUMPLESS_TYPE_DEFINITION_H
#define __STUMPLESS_TYPE_DEFINITION_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __STUMPLESS_HAVE_TIME_H
#include <time.h>
#endif

#include <stumpless/config.h>
#include <stumpless/type/declaration.h>

/**
 * An 8-bit word.
 */
typedef unsigned char Byte;

/**
 * The method of a particular HTTP request.
 */
enum HTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
};

/**
 * The methodology to use when sorting through a list.
 */
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

/**
 * An either true or false value.
 */
struct Boolean {
  unsigned short value; /**< the logical value */
  BooleanFormat *format; /**< the format to use for both values */
};

/**
 * The presentation for a Boolean value.
 */
struct BooleanFormat {
  const char *true_description; /**< the string to use for true values */
  const char *false_description; /**< the string to use for false values */
};

/**
 * An arbitrary sequence of Bytes.
 */
struct ByteList {
  Byte *bytes; /**< the array holding the Bytes */
  size_t capacity; /**< the size of the array */
  size_t count; /**< the number of Bytes in the list */
};

/**
 * A specific sorting definition for two objects.
 */
struct Comparator {
  /** the function to use to compare the objects */
  short ( *compare )( const Comparator *, const void *, const void * );
  const char *name; /**< the name of the comparator */
  Dictionary *options; /**< options to use in the comparisons */
};

/**
 * The configuration of a particular Logger.
 */
struct Configuration {
  FileConfiguration *file; /**< file configuration */
  HTTPConfiguration *http; /**< http configuration */
  SortingConfiguration *sorting; /**< sorting configuration */
  StringConfiguration *string; /**< string configuration */
  ThreadingConfiguration *threading; /**< threading configuration */
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

/**
 * File configuration options for a Logger.
 */
struct FileConfiguration {
  FILE *current_file; /**< the file currently begin logged to */
};

/**
 * Accept and reject various types of Records, Outputs, and Values.
 */
struct Filter {
  /** function to accept/reject Records */
  unsigned short ( *accept_record )( const Filter *, const Record * );
  /** function to accept/reject Output */
  unsigned short ( *accept_output )( const Filter *, const Output * );
  /** function to accept/reject Value */
  unsigned short ( *accept_value )( const Filter *, const Value * );
  const char *name; /**< the name of the Filter*/
  Dictionary *options; /**< options to use during filtering */
};

/**
 * Creates an Output for a Record in a specific format.
 */
struct Formatter {
  FilterList *filters; /**< filters to apply before formatting a Record */
  /** the function to format a Record */
  Output *( *format )( const Formatter *, const Record * );
  const char *name; /**< the unique name of the Formatter */
  Dictionary *options; /**< options to customize behavior */
};

/**
 * Takes an Output and send it via a receiver.
 */
struct Handler {
  FilterList *filters; /**< filters to apply before handling Output */
  Status *( *handle )( const Handler *, const Output * );
  const char *name; /**< the name of the Handler */
  Dictionary *options; /**< options to customize behavior */
};

/**
 * HTTP configuration options for a Logger.
 */
struct HTTPConfiguration {
  HTTPMethod method; /**< the method to use for an HTTP request */
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

/**
 * A collection of Records.
 *
 * @todo define records once the Tree structure is complete
 */
struct Log {
  //Tree *records;
  unsigned placeholder;
};

/**
 * A collection of logging targets and configuration parameters through which
 * logging can be accomplished.
 *
 * @todo change pipes to unix sockets
 */
struct Logger {
  AdapterList *adapters; /**< the Adapters to use on logged elements */
  Event *default_event; /**< the Event to assign Records by default */
  const char *name; /**< the unique name of the Logger */
  TargetList *targets; /**< the Targets to send logs to */
#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
  int receive_pipe; /**< the pipe used to receive messages */
  int send_pipe; /**< the pipe used to send messages */
#endif
};

/**
 * A container for a formatted Record.
 */
struct Output {
  ValueList *data; /**< the formatted data */
  OutputProfile *profile; /**< the profile to use to handle the data */
};

/**
 * Contains functions for working with formatted Records.
 */
struct OutputProfile {
  /** function to put an Output into a buffer */
  Status *( *into_buffer )( const Output * );
  /** function to send an Output using HTTP */
  Status *( *into_http )( const Output * );
  /** function to put an Output into a database */
  Status *( *into_mysql )( const Output * );
  /** function to put an Output into a stream */
  Status *( *into_stream )( const Output *, FILE * );
  /** function to put an Output into a string */
  Status *( *into_string )( const Output * );
  /** funciton to send an Output through a TCP socket */
  Status *( *into_tcp )( const Output * );
  /** checks to see if an Output is empty */
  unsigned short ( *is_empty )( const Output * );
  const char *name; /**< the name of the profile */
  /** creates a new string with the Output inside */
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

/**
 * A particular parameter of a Record.
 */
struct RecordAttribute {
  /** the EventAttribute this attribute is derived from */
  const EventAttribute *event_attribute;
  const char *name; /**< the name of the attribute */
  Value *value; /**< the value held in the attribute */
};

/**
 * The result of an operation without a perfect completion.
 */
struct Status {
  unsigned short error : 1; /**< there was a problem with the data */
  unsigned short failure : 1; /**< there was a system-caused problem */
  unsigned short warning : 1; /**< a non-fatal problem occurred */
  const char *description; /**< a description of the problem described */
  const char *name; /**< the name of the Status */
};

/**
 * A sorting configuration for a Logger.
 */
struct SortingConfiguration {
  SortingMethod record_method; /**< how to sort Records */
  SortingMethod log_method; /**< how to sort Logs */
  unsigned short ascending; /**< whether to sort ascending or descending */
};

/**
 * A string configuration for a Logger.
 */
struct StringConfiguration {
  size_t buffer_size; /**< the size to make string buffers by default */
};

/**
 * A specific Formatter/Handler pair to log to.
 */
struct Target {
  Formatter *formatter; /**< the Formatter to use on the Record */
  Handler *handler; /**< the destination of the Record */
};

/**
 * A threading configuration for a Logger.
 */
struct ThreadingConfiguration {
  unsigned short enabled : 1; /**< whether or not threading is enabled */
};

/**
 * A value in a Record.
 */
struct Value {
  /** the data represented */
  union {
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
  const char *format; /**< the format to use for the data */
  size_t length; /**< the length of the Value if, applicable */
  ValueProfile *profile; /**< the profile to use handling the data */
};

/**
 * A profile to use when working with Values.
 */
struct ValueProfile {
  /** Comparators to use when comparing Values */
  ComparatorList *comparators;
  /** puts the Value into a provided string */
  Status *( *into_string )( char *, const Value * );
  const char *name; /**< the name of the profile */
  /** creates a binary Output using the Value*/
  Output *( *to_binary )( const Formatter *, const Value * );
  /** creates a CSV Output using the Value */
  Output *( *to_csv )( const Formatter *, const Value * );
  /** creates a JSON Output using the Value */
  Output *( *to_json )( const Formatter *, const Value * );
  /** creates a string using the Value */
  char * ( *to_string )( const Value * );
  /** creates a text Output using the Value */
  Output *( *to_text )( const Formatter *, const Value * );
  /** creates a ValueLust using the Value */
  ValueList *( *to_value_list )( const Value * );
  /** creates an XML Output using the Value */
  Output *( *to_xml )( const Value * );
};

#endif
