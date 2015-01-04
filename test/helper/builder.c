#include <stdlib.h>

#include <stumpless/value.h>
#include <stumpless/value/constructor.h>
#include <stumpless/value/profile.h>

#include "private/adapter.h"
#include "private/comparator/base.h"
#include "private/configuration.h"
#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "private/container/list.h"
#include "private/container/list/adapter.h"
#include "private/container/list/comparator.h"
#include "private/container/list/const_iterator.h"
#include "private/container/list/filter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/handler.h"
#include "private/container/list/iterator.h"
#include "private/container/list/reverse_iterator.h"
#include "private/container/list/target.h"
#include "private/container/list/value.h"
#include "private/container/queue.h"
#include "private/container/stack.h"
#include "private/container/tree.h"
#include "private/filter.h"
#include "private/formatter.h"
#include "private/handler.h"
#include "private/output/profile.h"
#include "private/type.h"
#include "test/helper.h"

Adapter *
BuildAdapter
( void )
{
  Adapter *adapter;

  adapter = malloc( sizeof( Adapter ) );
  if( !adapter )
    return NULL;

  adapter->adapt = TestAdaptFunction;
  adapter->filters = NULL;
  adapter->name = "test adapter";
  adapter->options = BuildDictionaryOfStrings();

  return adapter;
}

AdapterList *
BuildAdapterList
( void )
{
  Adapter *adapter;
  AdapterList *list;

  list = NewAdapterList();
  if( !list )
    return NULL;

  adapter = BuildAdapter();
  if( !adapter )
    return NULL;
  if( !AppendToAdapterList( list, adapter ) )
    return NULL;

  adapter = BuildBadAdapter();
  if( !adapter )
    return NULL;
  if( !AppendToAdapterList( list, adapter ) )
    return NULL;

  return list;
}

Adapter *
BuildBadAdapter
( void )
{
  Adapter *adapter;

  adapter = malloc( sizeof( Adapter ) );
  if( !adapter )
    return NULL;

  adapter->adapt = BadAdaptFunction;
  adapter->filters = NULL;
  adapter->name = "bad adapter";
  adapter->options = BuildDictionaryOfStrings();

  return adapter;
}

Formatter *
BuildBadFormatter
( void )
{
  Formatter *formatter;

  formatter = malloc( sizeof( Formatter ) );
  if( !formatter )
    return NULL;

  formatter->name = "test formatter";
  formatter->options = BuildDictionaryOfStrings();
  if( !formatter->options )
    return NULL;

  formatter->filters = BuildFilterList();
  if( !formatter->filters )
    return NULL;

  formatter->format = BadFormatFunction;

  return formatter;
}

Handler *
BuildBadHandler
( void )
{
  Handler *handler;

  handler = malloc( sizeof( Handler ) );
  if( !handler )
    return NULL;

  handler->name = "bad handler";

  handler->filters = BuildFilterList();
  if( !handler->filters )
    return NULL;

  handler->options = BuildDictionaryOfStrings();
  if( !handler->options )
    return NULL;

  handler->handle = BadHandleFunction;

  return handler;
}

Target *
BuildBadTarget
( void )
{
  Target *target;

  target = malloc( sizeof( Target ) );
  if( !target )
    return NULL;

  target->formatter = BuildBadFormatter();
  if( !target->formatter )
    return NULL;

  target->handler = BuildBadHandler();
  if( !target->handler )
    return NULL;

  return target;
}

Boolean *
BuildBoolean
( void )
{
  Boolean *boolean;

  boolean = malloc( sizeof( Boolean ) );
  if( !boolean )
    return NULL;

  boolean->format = malloc( sizeof( BooleanFormat ) );
  if( !boolean->format )
    return NULL;

  boolean->value = 1;
  boolean->format->true_description = "true";
  boolean->format->false_description = "false";

  return boolean;
}

Value *
BuildBooleanValue
( void )
{
  Boolean *boolean;
  Value *value;

  boolean = BuildBoolean();
  if( !boolean )
    return NULL;

  value = NewValueForBoolean( boolean );
  if( !value )
    return NULL;

  return value;
}

Output *
BuildByteOutput( void )
{
  Output *output;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "binary" );
  if( !output->profile )
    return NULL;

  return output;
}

Value *
BuildCharArrayValue
( void )
{
  char *array;
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "char array" );
  if( !value->profile )
    return NULL;

  array = malloc( sizeof( char ) * 10 );
  if( !array )
    return NULL;

  array[0] = 'a';
  array[1] = 'b';
  array[2] = 'c';
  array[3] = 'd';
  array[4] = 'e';
  array[5] = 'f';
  array[6] = 'g';
  array[7] = 'h';
  array[8] = 'i';
  array[9] = 'j';

  value->c_p = array;
  value->length = 10;

  return value;
}

Comparator *
BuildComparator
( void )
{
  Comparator *comparator;

  comparator = malloc( sizeof( Comparator ) );
  if( !comparator )
    return NULL;

  comparator->compare = StringComparatorCompare;
  comparator->options = BuildDictionaryOfStrings();
  if( !comparator->options )
    return NULL;

  return comparator;
}

ComparatorList *
BuildComparatorList
( void )
{
  Comparator *comparator;
  ComparatorList *list;

  list = NewComparatorList();
  if( !list )
    return NULL;

  comparator = BuildComparator();
  if( !comparator )
    return NULL;
  if( !AppendToComparatorList( list, comparator ) )
    return NULL;

  comparator = BuildComparator();
  if( !comparator )
    return NULL;
  if( !AppendToComparatorList( list, comparator ) )
    return NULL;

  return list;
}

DictionaryConstIterator *
BuildDictionaryConstIterator
( void )
{
  return CBeginDictionary( BuildDictionaryOfStrings() );
}

Dictionary *
BuildDictionaryOfEventAttributes
( void )
{
  Dictionary *attributes;
  EventAttribute *attribute;

  attributes = NewDictionary();
  if( !attributes )
    return NULL;

  attribute = malloc( sizeof( EventAttribute ) );
  if( !attribute )
    return NULL;
  attribute->name = "Test Attribute 1";
  attribute->default_value = NewValueForString( "default value" );
  SetDictionaryValue( attributes, attribute->name, attribute );

  attribute = malloc( sizeof( EventAttribute ) );
  if( !attribute )
    return NULL;
  attribute->name = "Test Attribute 2";
  attribute->default_value = NULL;
  SetDictionaryValue( attributes, attribute->name, attribute );

  attribute = malloc( sizeof( EventAttribute ) );
  if( !attribute )
    return NULL;
  attribute->name = "Unused Attribute";
  attribute->default_value = NULL;
  SetDictionaryValue( attributes, attribute->name, attribute );

  return attributes;
}

Dictionary *
BuildDictionaryOfRecordAttributes
( void )
{
  Dictionary *event_attributes, *record_attributes;
  DictionaryConstIterator *iterator;
  const EventAttribute *event_attribute;
  RecordAttribute *record_attribute;

  record_attributes = NewDictionary();
  if( !record_attributes )
    return NULL;

  event_attributes = BuildDictionaryOfEventAttributes();
  if( !event_attributes )
    return NULL;

  iterator = CBeginDictionary( event_attributes );
  while( event_attribute = NextInDictionaryConstIterator( iterator ) ){
    if( strcmp( event_attribute->name, "Unused Attribute" ) == 0)
      continue;

    record_attribute = malloc( sizeof( RecordAttribute ) );
    if( !record_attribute )
      return NULL;

    record_attribute->name = event_attribute->name;
    record_attribute->event_attribute = event_attribute;
    record_attribute->value = event_attribute->default_value;
    if( !record_attribute->value )
      record_attribute->value = NewValueForString( "attribute value" );

    SetDictionaryValue( record_attributes, record_attribute->name, record_attribute );
  }

  record_attribute = malloc( sizeof( RecordAttribute ) );
  if( !record_attribute )
    return NULL;

  record_attribute->name = "Anonymous Attribute";
  record_attribute->event_attribute = NULL;
  record_attribute->value = NewValueForString( "anonymous attribute value" );

  SetDictionaryValue( record_attributes, record_attribute->name, record_attribute );

  return record_attributes;
}

Dictionary *
BuildDictionaryOfStrings
( void )
{
  Dictionary *dictionary;

  dictionary = NewDictionary();
  if( !dictionary )
    return NULL;

  SetDictionaryValue( dictionary, "first", "1st" );
  SetDictionaryValue( dictionary, "second", "2nd" );
  SetDictionaryValue( dictionary, "third", "3rd" );

  return dictionary;
}

Record *
BuildEmptyRecord
( void )
{
  Record *record = malloc( sizeof( Record ) );
  if( !record )
    return NULL;

  record->event = NULL;
  record->attributes = NULL;

  return record;
}

Output *
BuildEmptyOutput
( void )
{
  Output * output = malloc( sizeof( Output ) );
  if( output == NULL )
    return NULL;

  output->data = NULL;
  output->profile = BuildOutputProfile();
  if( output->profile == NULL )
    return NULL;

  return output;
}

Value *
BuildEmptyUnsignedIntArrayValue
( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "unsigned int array" );
  if( !value->profile )
    return NULL;

  value->u_i_p = malloc( sizeof( unsigned ) * 10 );
  if( !value->u_i_p )
    return NULL;

  value->length = 0;

  return value;
}

Value *
BuildEmptyValue
( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;
  value->length = 0;
  value->profile = BuildValueProfile();
  if( !value->profile )
    return NULL;

  return value;
}

Status *
BuildErrorStatus
( void )
{
  Status * status = malloc( sizeof( Status ) );
  if( status == NULL )
    return NULL;

  status->error = 1;
  status->failure = 0;
  status->warning = 0;

  status->name = "test error status";
  status->description = "this status is meant to mimic a generic status that points at some error. Use it for testing purposes only.";

  return status;
}

Event *
BuildEvent
( void )
{
  Event *event = malloc( sizeof( Event ) );
  if( !event )
    return NULL;

  event->name = "Test Event";

  event->level = BuildLevel();
  if( !event->level )
    return NULL;

  event->attributes = BuildDictionaryOfEventAttributes();
  if( !event->attributes )
    return NULL;

  return event;
}

EventAttribute *
BuildEventAttribute
( void )
{
  EventAttribute * attribute;
  attribute = malloc( sizeof( EventAttribute ) );
  if( !attribute )
    return NULL;

  attribute->name = "Test Event Attribute";
  attribute->default_value = NewValueForString( "Test Default Value" );

  return attribute;
}

Status *
BuildFailureStatus
( void )
{
  Status * status = malloc( sizeof( Status ) );
  if( status == NULL )
    return NULL;

  status->error = 0;
  status->failure = 1;
  status->warning = 0;

  status->name = "test failure status";
  status->description = "this status is meant to mimic a generic status that points at a failure of a function to finish. Use it for testing purposes only.";

  return status;
}

Filter *
BuildFilter
( void )
{
  Filter * filter = malloc( sizeof( Filter ) );
  if( filter == NULL )
    return NULL;

  filter->name = "test filter";
  filter->options = BuildDictionaryOfStrings();
  if( filter->options == NULL )
    return NULL;

  return filter;
}

FilterList *
BuildFilterList
( void )
{
  Filter *filter;
  FilterList *list;

  list = NewFilterList();
  if( !list )
    return NULL;

  filter = FindFilterByName( "empty" );
  if( !filter )
    return NULL;
  AppendToFilterList( list, filter );

  filter = FindFilterByName( "level" );
  if( !filter )
    return NULL;
  AppendToFilterList( list, filter );

  return list;
}

Formatter *
BuildFormatter
( void )
{
  Formatter *formatter;

  formatter = malloc( sizeof( Formatter ) );
  if( !formatter )
    return NULL;

  formatter->name = "test formatter";
  formatter->options = BuildDictionaryOfStrings();
  if( !formatter->options )
    return NULL;

  formatter->filters = BuildFilterList();
  if( !formatter->filters )
    return NULL;

  formatter->format = TestFormatFunction;

  return formatter;
}

FormatterList *
BuildFormatterList
( void )
{
  Formatter *formatter;
  FormatterList *list;

  list = NewFormatterList();
  if( !list )
    return NULL;

  formatter = FindFormatterByName( "csv" );
  if( !formatter )
    return NULL;
  if( !AppendToFormatterList( list, formatter ) )
    return NULL;

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return NULL;
  if( !AppendToFormatterList( list, formatter ) )
    return NULL;

  return list;
}

Handler *
BuildHandler
( void )
{
  Handler *handler;

  handler = malloc( sizeof( Handler ) );
  if( !handler )
    return NULL;

  handler->name = "test handler";
  handler->options = BuildDictionaryOfStrings();
  if( !handler->options )
    return NULL;

  handler->handle = TestHandleFunction;

  return handler;
}

HandlerList *
BuildHandlerList
( void )
{
  Handler *handler;
  HandlerList *list;

  list = NewHandlerList();
  if( !list )
    return NULL;

  handler = BuildHandler();
  if( !handler )
    return NULL;
  if( !AppendToHandlerList( list, handler ) )
    return NULL;

  handler = BuildHandler();
  if( !handler )
    return NULL;
  if( !AppendToHandlerList( list, handler ) )
    return NULL;

  return list;
}

Value *
BuildIntArrayValue( void )
{
  int *array;
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "int array" );
  if( value->profile == NULL )
    return NULL;

  array = malloc( sizeof( int ) * 10 );
  if( !array )
    return NULL;

  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  array[3] = 3;
  array[4] = 4;
  array[5] = 5;
  array[6] = 6;
  array[7] = 7;
  array[8] = 8;
  array[9] = 9;

  value->i_p = array;
  value->length = 10;

  return value;
}

Value *
BuildIntValue
( void )
{
  return NewValueForInt( 45678 );
}

Level *
BuildLevel
( void )
{
  Level *level;

  level = malloc( sizeof( Level ) ) ;
  if( !level )
    return NULL;

  level->name = "Test Level";
  level->primary = 42;
  level->secondary = 31;
  level->tertiary = 7;

  return level;
}

ListConstIterator *
BuildListConstIterator
( void )
{
  ListConstIterator *iterator;

  iterator = NewListConstIterator( BuildListOfStrings(), 0 );
  if( !iterator )
    return NULL;

  return iterator;
}

ListIterator *
BuildListIterator
( void )
{
  ListIterator *iterator;

  iterator = NewListIterator( BuildListOfStrings(), 0 );
  if( !iterator )
    return NULL;

  return iterator;
}

List *
BuildListOfStrings
( void )
{
  List *list;

  list = NewList();
  if( !list )
    return NULL;

  AppendToList( list, "This" );
  AppendToList( list, "is" );
  AppendToList( list, "a" );
  AppendToList( list, "test" );
  AppendToList( list, "list" );
  AppendToList( list, "o'" );
  AppendToList( list, "Strings!" );

  return list;
}

ListReverseIterator *
BuildListReverseIterator
( void )
{
  ListReverseIterator *iterator;

  iterator = NewListReverseIterator( BuildListOfStrings(), 0 );
  if( !iterator )
    return NULL;

  return iterator;
}

Logger *
BuildLogger
( void )
{
  Logger *logger;

  logger = malloc( sizeof( Logger ) );
  if( !logger )
    return NULL;

  logger->name = "test logger";

  logger->adapters = BuildAdapterList();
  if( !logger->adapters )
    return NULL;

  logger->targets = BuildTargetList();
  if( !logger->targets )
    return NULL;

  return logger;
}

Output *
BuildOutput
( void )
{
  Output *output;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = BuildValueList();
  if( !output->data )
    return NULL;

  output->profile = BuildOutputProfile();
  if( !output->profile )
    return NULL;

  return output;
}

OutputProfile *
BuildOutputProfile
( void )
{
  OutputProfile *profile;

  profile = malloc( sizeof( OutputProfile ) );
  if( !profile )
    return NULL;

  profile->into_mysql = NULL;
  profile->into_stream = NULL;
  profile->into_string = NULL;
  profile->into_tcp = NULL;
  profile->name = "Test Profile";
  profile->to_string = NULL;

  return profile;
}

Queue *
BuildQueue
( void )
{
  Queue *queue;

  queue = NewQueue();
  if( !queue )
    return NULL;

  PushToQueue( queue, "first element" );
  PushToQueue( queue, "second element");
  PushToQueue( queue, "third element" );

  return queue;
}

Output *
BuildRawStringOutput
( void )
{
  Output *output;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "raw string" );
  if( !output->profile )
    return NULL;

  output->data = NewValueList();
  if( !output->data )
    return NULL;

  AppendStringToValueList( output->data, "Test String with\nstuff in it." );

  return output;
}

Record *
BuildRecord
( void )
{
  Record *record;

  record = malloc( sizeof( Record ) );
  if( !record )
    return NULL;

  record->event = BuildEvent();
  if( !record->event )
    return NULL;

  record->attributes = BuildDictionaryOfRecordAttributes();
  if( !record->attributes )
    return NULL;

  return record;
}

RecordAttribute *
BuildRecordAttribute
( void )
{
  RecordAttribute *attribute;

  attribute = malloc( sizeof( RecordAttribute ) );
  if( !attribute )
    return NULL;

  attribute->event_attribute = BuildEventAttribute();
  if( !attribute->event_attribute )
    return NULL;

  attribute->name = attribute->event_attribute->name;

  attribute->value = NewValueForString( "Test Value" );
  if( !attribute->value )
    return NULL;

  return attribute;
}

Stack *
BuildStackOfStrings
( void )
{
  Stack *stack;

  stack = NewStack();
  if( !stack )
    return NULL;

  if( !PushToStack( stack, "bottom" ) )
    return NULL;

  if( !PushToStack( stack, "middle" ) )
    return NULL;

  if( !PushToStack( stack, "top" ) )
    return NULL;

  return stack;
}

Value *
BuildStringValue
( void )
{
  Value *value;

  value = malloc( sizeof( Value * ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "string" );
  if( !value->profile )
    return NULL;

  value->c_p = "Test String Value";

  return value;
}

Target *
BuildTarget
( void )
{
  Target *target;

  target = malloc( sizeof( Target ) );
  if( !target )
    return NULL;

  target->formatter = BuildFormatter();
  if( !target->formatter )
    return NULL;

  target->handler = BuildHandler();
  if( !target->handler )
    return NULL;

  return target;
}

TargetList *
BuildTargetList
( void )
{
  TargetList *list;

  list = NewTargetList();
  if( !list )
    return NULL;

  AppendToTargetList( list, BuildTarget() );
  AppendToTargetList( list, BuildBadTarget() );

  return list;
}

Output *
BuildTextOutput
( void )
{
  Output *output;
  ValueList *result, *values;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;

  values = NewValueList();
  if( !values )
    return NULL;

  result = AppendStringToValueList( values, "First\n" );
  if( !result )
    return NULL;

  result = AppendStringToValueList( values, "Second\n" );
  if( !result )
    return NULL;

  result = AppendStringToValueList( values, "Third" );
  if( !result )
    return NULL;

  output->data = values;

  return output;
}

Tree *
BuildTreeOfStrings
( void )
{
  Tree *tree;

  tree = NewTree();
  if( !tree )
    return NULL;

  if( !AddComparatorToTree( tree, BuildComparator() ) )
    return NULL;

  if( !AddToTree( tree, "first" ) )
    return NULL;

  if( !AddToTree( tree, "second" ) )
    return NULL;

  return AddToTree( tree, "third" );
}

Value *
BuildUnsignedIntValue
( void )
{
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "unsigned int" );
  if( !value->profile )
    return NULL;

  value->u_i = 4294967196u;

  return value;
}

Value *
BuildUnsignedShortValue
( void )
{
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "unsigned short" );
  if( !value->profile )
    return NULL;

  value->u_s = 65000u;

  return value;
}

Value *
BuildValue
( void )
{
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;
  value->profile = FindValueProfileByName( "unsigned short" );
  if( !value->profile )
    return NULL;

  value->u_s = 6500u;

  return value;
}

ValueList *
BuildValueList
( void )
{
  Value *value;
  ValueList *list, *result;

  list = NewValueList();
  if( !list )
    return NULL;

  value = BuildIntArrayValue();
  if( !value )
    return NULL;
  result = AppendToValueList( list, value );
  if( !result )
    return NULL;

  value = BuildUnsignedIntValue();
  if( !value )
    return NULL;
  result = AppendToValueList( list, value );
  if( !result )
    return NULL;

  value = BuildUnsignedShortValue();
  if( !value )
    return NULL;
  result = AppendToValueList( list, value );
  if( !result )
    return NULL;

  value = BuildCharArrayValue();
  if( value == NULL )
    return NULL;
  result = AppendToValueList( list, value );
  if( !result )
    return NULL;

  value = BuildVoidValue();
  if( !value )
    return NULL;
  result = AppendToValueList( list, value );
  if( !result )
    return NULL;

  return list;
}

ValueList *
BuildValueListOfStrings( void )
{
  ValueList *list;

  list = NewValueList();
  if( !list )
    return NULL;

  AppendStringToValueList( list, "this" );
  AppendStringToValueList( list, "is" );
  AppendStringToValueList( list, "a" );
  AppendStringToValueList( list, "test" );
  AppendStringToValueList( list, "list" );

  return list;
}

ValueProfile *
BuildValueProfile
( void )
{
  ValueProfile *profile;

  profile = malloc( sizeof( ValueProfile ) );
  if( !profile )
    return NULL;

  profile->name = "Test Profile";
  profile->to_binary = NULL;
  profile->to_csv = NULL;
  profile->to_json = NULL;
  profile->to_string = NULL;
  profile->to_text = NULL;
  profile->to_value_list = NULL;
  profile->to_xml = NULL;

  return profile;
}

Value *
BuildVoidValue
( void )
{
  Boolean *boolean;
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "boolean" );
  if( !value->profile )
    return NULL;

  boolean = BuildBoolean();
  if( !boolean )
    return NULL;

  value->v_p = (void *) boolean;

  return value;
}

Status *
BuildWarningStatus
( void )
{
  Status *status;

  status = malloc( sizeof( Status ) );
  if( !status )
    return NULL;

  status->error = 0;
  status->failure = 0;
  status->warning = 1;

  status->name = "test warning status";
  status->description = "this status is meant to mimic a generic status that seeks to warn of something that may turn into an error. Use it for testing purposes only.";

  return status;
}
