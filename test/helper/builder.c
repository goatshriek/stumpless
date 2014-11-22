#include <stdlib.h>

#include "private/adapter.h"
#include "private/comparator/base.h"
#include "private/configuration.h"
#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "private/container/list.h"
#include "private/container/list/adapter.h"
#include "private/container/list/comparator.h"
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
#include "private/value/constructor.h"
#include "private/value/profile.h"
#include "test/helper.h"

Adapter *
BuildAdapter
( void )
{
  Adapter *adapter = malloc( sizeof( Adapter ) );
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
  AdapterList *list = NewAdapterList();
  if( !list )
    return NULL;

  Adapter *adapter = BuildAdapter();
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
  Adapter *adapter = malloc( sizeof( Adapter ) );
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
  Formatter *formatter = malloc( sizeof( Formatter ) );
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
  Handler *handler = malloc( sizeof( Handler ) );
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
  Target *target = malloc( sizeof( Target ) );
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
  Boolean * boolean = malloc( sizeof( Boolean ) );
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
  Boolean * boolean = BuildBoolean();
  if( !boolean )
    return NULL;

  Value *value = NewValueForBoolean( boolean );
  if( !value )
    return NULL;

  return value;
}

Output *
BuildByteOutput( void )
{
  Output * output;
  output = malloc( sizeof( Output ) );
  if( output == NULL )
    return NULL;

  output->profile = FindOutputProfileByName( "binary" );
  if( output->profile == NULL )
    return NULL;

  return output;
}

Value *
BuildCharArrayValue
( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->profile = FindValueProfileByName( "char array" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  char * array = malloc( sizeof( char ) * 10 );
  if( array == NULL )
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

  value->data->c_p = array;
  value->length = 10;

  return value;
}

Comparator *
BuildComparator
( void )
{
  Comparator *comparator = malloc( sizeof( Comparator ) );
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
  ComparatorList *list = NewComparatorList();
  if( !list )
    return NULL;

  Comparator *comparator = BuildComparator();
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
  Dictionary *attributes = NewDictionary();
  if( !attributes )
    return NULL;

  EventAttribute *attribute;
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
  Dictionary *record_attributes = NewDictionary();
  if( !record_attributes )
    return NULL;

  Dictionary *event_attributes = BuildDictionaryOfEventAttributes();
  if( !event_attributes )
    return NULL;

  RecordAttribute *record_attribute;
  const EventAttribute *event_attribute;
  DictionaryConstIterator *iterator = CBeginDictionary( event_attributes );
  while( event_attribute = NextInDictionaryConstIterator( iterator ) ){
    record_attribute = malloc( sizeof( RecordAttribute ) );
    if( !record_attribute )
      return NULL;

    record_attribute->event_attribute = event_attribute;
    record_attribute->value = event_attribute->default_value;
    if( !record_attribute->value )
      record_attribute->value = NewValueForString( "attribute value" );

    SetDictionaryValue( record_attributes, event_attribute->name, record_attribute );
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
  Dictionary *dictionary = NewDictionary();
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
  if( value == NULL )
    return NULL;

  value->profile = FindValueProfileByName( "unsigned int array" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  value->data->u_i_p = malloc( sizeof( unsigned ) * 10 );
  if( value->data->u_i_p == NULL )
    return NULL;

  value->length = 0;

  return value;
}

Value *
BuildEmptyValue
( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->data = NULL;
  value->format = NULL;
  value->length = 0;
  value->profile = BuildValueProfile();
  if( value->profile == NULL )
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
  FilterList * list = NewFilterList();
  if( list == NULL )
    return NULL;

  Filter * filter = FindFilterByName( "empty" );
  if( filter == NULL )
    return NULL;
  AppendToFilterList( list, filter );

  filter = FindFilterByName( "level" );
  if( filter == NULL )
    return NULL;
  AppendToFilterList( list, filter );

  return list;
}

Formatter *
BuildFormatter
( void )
{
  Formatter *formatter = malloc( sizeof( Formatter ) );
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
  FormatterList *list = NewFormatterList();
  if( !list )
    return NULL;

  Formatter * formatter = FindFormatterByName( "csv" );
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
  Handler *handler = malloc( sizeof( Handler ) );
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
  HandlerList *list = NewHandlerList();
  if( !list )
    return NULL;

  Handler *handler = BuildHandler();
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
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "int array" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  int * array = malloc( sizeof( int ) * 10 );
  if( array == NULL )
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

  value->data->i_p = array;
  value->length = 10;

  return value;
}

Value *
BuildIntValue( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  value->profile = FindValueProfileByName( "int" );
  if( value->profile == NULL )
    return NULL;

  value->data->i = 45678;

  return value;
}

Level *
BuildLevel
( void )
{
  Level *level = malloc( sizeof( Level ) ) ;
  if( !level )
    return NULL;

  level->name = "Test Level";
  level->primary = 42;
  level->secondary = 31;
  level->tertiary = 7;

  return level;
}

ListIterator *
BuildListIterator
( void )
{
  ListIterator * iterator = NewListIterator( BuildListOfStrings(), 0 );
  if( !iterator )
    return NULL;

  return iterator;
}

List *
BuildListOfStrings
( void )
{
  List * list = NewList();
  if( list == NULL )
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
  ListReverseIterator * iterator = NewListReverseIterator( BuildListOfStrings(), 0 );
  if( !iterator )
    return NULL;

  return iterator;
}

Logger *
BuildLogger
( void )
{
  Logger *logger = malloc( sizeof( Logger ) );
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
  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data )
    return NULL;

  output->data->c = 'a';
  output->profile = BuildOutputProfile();
  if( !output->profile )
    return NULL;

  return output;
}

OutputProfile *
BuildOutputProfile
( void )
{
  OutputProfile * profile = malloc( sizeof( OutputProfile ) );
  if( profile == NULL )
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
  Queue *queue = NewQueue();
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
  Output * output = malloc( sizeof( Output ) );
  if( output == NULL )
    return NULL;

  output->profile = FindOutputProfileByName( "raw string" );
  if( output->profile == NULL )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( output->data == NULL )
    return NULL;

  output->data->c_p = "Test String with\nstuff in it.";

  return output;
}

Record *
BuildRecord( void )
{
  Record *record = malloc( sizeof( Record ) );
  if( !record )
    return NULL;

  record->event = BuildEvent();
  record->attributes = BuildDictionaryOfRecordAttributes();

  return record;
}

RecordAttribute *
BuildRecordAttribute
( void )
{
  RecordAttribute * attribute;
  attribute = malloc( sizeof( RecordAttribute ) );
  if( attribute == NULL )
    return NULL;

  attribute->event_attribute = BuildEventAttribute();
  attribute->value = NewValueForString( "Test Value" );

  return attribute;
}

Stack *
BuildStackOfStrings
( void )
{
  Stack * stack = NewStack();
  if( stack == NULL )
    return NULL;

  if( PushToStack( stack, "bottom" ) == NULL )
    return NULL;

  if( PushToStack( stack, "middle" ) == NULL )
    return NULL;

  if( PushToStack( stack, "top" ) == NULL )
    return NULL;

  return stack;
}

Value *
BuildStringValue
( void )
{
  Value * value = malloc( sizeof( Value * ) );
  if( value == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  value->profile = FindValueProfileByName( "string" );
  if( value->profile == NULL )
    return NULL;

  value->data->c_p = "Test String Value";

  return value;
}

Target *
BuildTarget
( void )
{
  Target *target = malloc( sizeof( Target ) );
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
  TargetList *list = NewTargetList();
  if( !list )
    return NULL;

  AppendToTargetList( list, BuildTarget() );
  AppendToTargetList( list, BuildBadTarget() );

  return list;
}

Output *
BuildTextOutput( void )
{
  Output * output = malloc( sizeof( Output ) );
  if( output == NULL )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( output->profile == NULL )
    return NULL;

  ValueList * values = NewValueList();
  if( values == NULL )
    return NULL;

  ValueList * result = AppendStringToValueList( values, "First\n" );
  if( !result )
    return NULL;

  result = AppendStringToValueList( values, "Second\n" );
  if( !result )
    return NULL;

  result = AppendStringToValueList( values, "Third" );
  if( !result )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( output->data == NULL )
    return NULL;

  output->data->v_p = ( void * ) values;

  return output;
}

Tree *
BuildTreeOfStrings
( void )
{
  Tree * tree = NewTree();
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
BuildUnsignedIntValue( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "unsigned int" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;
  value->data->u_i = 4294967196u;

  return value;
}

Value *
BuildUnsignedShortValue( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->format = NULL;

  value->profile = FindValueProfileByName( "unsigned short" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;
  value->data->u_s = 65000u;

  return value;
}

Value *
BuildValue
( void )
{
  Value *value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->format = NULL;
  value->profile = FindValueProfileByName( "unsigned short" );
  if( !value->profile )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( !value->data )
    return NULL;
  value->data->u_s = 6500u;

  return value;
}

ValueList *
BuildValueList
( void )
{
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;

  Value * value;
  ValueList * result;

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
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;

  AppendStringToValueList( list, "this" );
  AppendStringToValueList( list, "is" );
  AppendStringToValueList( list, "a" );
  AppendStringToValueList( list, "test" );
  AppendStringToValueList( list, "list" );

  return list;
}

ValueProfile *
BuildValueProfile( void )
{
  ValueProfile * profile = malloc( sizeof( ValueProfile ) );
  if( profile == NULL )
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
BuildVoidValue( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;

  value->profile = FindValueProfileByName( "boolean" );
  if( value->profile == NULL )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( value->data == NULL )
    return NULL;

  Boolean * boolean = BuildBoolean();
  if( boolean == NULL )
    return NULL;

  value->data->v_p = (void *) boolean;

  return value;
}

Status *
BuildWarningStatus
( void )
{
  Status * status = malloc( sizeof( Status ) );
  if( status == NULL )
    return NULL;

  status->error = 0;
  status->failure = 0;
  status->warning = 1;

  status->name = "test warning status";
  status->description = "this status is meant to mimic a generic status that seeks to warn of something that may turn into an error. Use it for testing purposes only.";

  return status;
}
