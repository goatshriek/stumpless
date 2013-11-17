#include <stdlib.h>

#include "private/configuration.h"
#include "private/dictionary.h"
#include "private/filter.h"
#include "private/filter_list.h"
#include "private/handler_list.h"
#include "private/list.h"
#include "private/output_profile.h"
#include "private/type.h"
#include "private/value_constructor.h"
#include "private/value_list.h"
#include "private/value_profile.h"

#include "builder.h"

Boolean *
BuildBoolean( void )
{
  Boolean * boolean = malloc( sizeof( Boolean ) );
  if( boolean == NULL )
    return NULL;
  
  boolean->format = malloc( sizeof( BooleanFormat ) );
  if( boolean->format == NULL )
    return NULL;
  
  boolean->value = 1;
  boolean->format->true_description = "true";
  boolean->format->false_description = "false";
  
  return boolean;
}

Value *
BuildBooleanValue( void )
{
  Boolean * boolean = BuildBoolean();
  if( boolean == NULL )
    return NULL;
  
  Value * value = ValueFromBoolean( boolean );
  if( value == NULL )
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
BuildCharArrayValue( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return NULL;
  
  value->profile = FindValueProfileByName( "char array" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( Type ) );
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

Dictionary *
BuildDictionaryOfStrings
( void )
{
  Dictionary * dictionary = NewDictionary();
  if( dictionary == NULL )
    return NULL;
  
  SetDictionaryValue( dictionary, "first", "1st" );
  SetDictionaryValue( dictionary, "second", "2nd" );
  SetDictionaryValue( dictionary, "third", "3rd" );
  
  return dictionary;
}

Entry *
BuildEmptyEntry
( void )
{
  Entry * entry = malloc( sizeof( Entry ) );
  if( entry == NULL )
    return NULL;
  
  entry->description = NULL;
  entry->event = NULL;
  entry->attributes = NULL;
  entry->attribute_count = 0;
  
  return entry;
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
  
  value->data = malloc( sizeof( Type ) );
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

Entry *
BuildEntry( void )
{
  Entry * entry = malloc( sizeof( Entry ) );
  if( entry == NULL )
    return NULL;
  
  entry->description = "Test Entry";
  entry->event = BuildEvent();
  entry->attributes = BuildEntryAttributeList();
  entry->attribute_count = 6;
  
  return entry;
}

EntryAttribute *
BuildEntryAttribute( void )
{
  EntryAttribute * attribute;
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  
  attribute->event_attribute = BuildEventAttribute();
  attribute->value = ValueFromString( "Test Value" );
  
  return attribute;
}

EntryAttribute **
BuildEntryAttributeList( void )
{
  EntryAttribute ** list;
  list = malloc( sizeof( EntryAttribute * ) * 6 );
  if( list == NULL )
    return NULL;
  
  EventAttribute ** event_attribute_list = BuildEventAttributeList();
  if( event_attribute_list == NULL )
    return NULL;
  
  EntryAttribute * attribute;
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[0];
  attribute->value = NULL;
  list[0] = attribute;
  
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[1];
  attribute->value = ValueFromString( "not 37" );
  list[1] = attribute;
  
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[2];
  attribute->value = NULL;
  list[2] = attribute;
  
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[3];
  attribute->value = ValueFromString( "unnamed value" );
  list[3] = attribute;
  
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = NULL;
  attribute->value = ValueFromString( "no event attribute" );
  list[4] = attribute;
  
  attribute = malloc( sizeof( EntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = NULL;
  attribute->value = NULL;
  list[5] = attribute;
  
  return list;
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
BuildEvent( void )
{
  Event * event = malloc( sizeof( Event ) );
  if( event == NULL )
    return NULL;
  
  event->name = "Test Event";
  
  event->level = BuildLevel();
  if( event->level == NULL )
    return NULL;
  
  event->attributes = BuildEventAttributeList();
  if( event->attributes == NULL )
    return NULL;
  event->attribute_count = 5;
  
  return event;
}

EventAttribute *
BuildEventAttribute( void )
{
  EventAttribute * attribute;
  attribute = malloc( sizeof( EventAttribute ) );
  if( attribute == NULL )
    return NULL;
  
  attribute->name = "Test Event Attribute";
  attribute->default_value = ValueFromString( "Test Default Value" );
  
  return attribute;
}

EventAttribute **
BuildEventAttributeList( void )
{
  EventAttribute ** list;
  list = malloc( sizeof( EventAttribute * ) * 5 );
  if( list == NULL )
    return NULL;
  
  EventAttribute * attr_0;
  attr_0 = malloc( sizeof( EventAttribute ) );
  if( attr_0 == NULL )
    return NULL;
  attr_0->name = "Test Attribute 0";
  attr_0->default_value = ValueFromString( "default value" );
  
  EventAttribute * attr_1;
  attr_1 = malloc( sizeof( EventAttribute ) );
  if( attr_1 == NULL )
    return NULL;
  attr_1->name = NULL;
  attr_1->default_value = ValueFromUnsignedInt( 37 );
  
  EventAttribute * attr_2;
  attr_2 = malloc( sizeof( EventAttribute ) );
  if( attr_2 == NULL )
    return NULL;
  attr_2->name = "Test Attribute 2";
  attr_2->default_value = NULL;
  
  EventAttribute * attr_3;
  attr_3 = malloc( sizeof( EventAttribute ) );
  if( attr_3 == NULL )
    return NULL;
  attr_3->name = NULL;
  attr_3->default_value = NULL;
  
  list[0] = attr_0;
  list[1] = attr_1;
  list[2] = attr_2;
  list[3] = attr_3;
  list[4] = NULL;
  
  return list;
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

Handler *
BuildHandler
( void )
{
  Handler * handler = malloc( sizeof( Handler ) );
  if( handler == NULL )
    return NULL;
  
  handler->name = "test handler";
  handler->options = BuildDictionaryOfStrings();
  if( handler->options == NULL )
    return NULL;
  
  return handler;
}

HandlerList *
BuildHandlerList
( void )
{
  HandlerList * list = NewHandlerList();
  if( list == NULL )
    return NULL;
  
  Handler * handler = malloc( sizeof( Handler ) );
  if( handler == NULL )
    return NULL;
  handler->name = "first handler";
  AppendToHandlerList( list, handler );
  
  handler = malloc( sizeof( Handler ) );
  if( handler == NULL )
    return NULL;
  handler->name = "second handler";
  AppendToHandlerList( list, handler );
  
  handler = malloc( sizeof( Handler ) );
  if( handler == NULL )
    return NULL;
  handler->name = "third handler";
  AppendToHandlerList( list, handler );
  
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
  
  value->data = malloc( sizeof( Type ) );
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
  
  value->data = malloc( sizeof( Type ) );
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
  Level * level = malloc( sizeof( Level ) ) ;
  if( level == NULL )
    return NULL;
  
  level->name = "Test Level";
  level->value = 42;
  
  return level;
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
  
  output->data = malloc( sizeof( Type ) );
  if( output->data == NULL )
    return NULL;
  
  output->data->c_p = "Test String with\nstuff in it.";
  
  return output;
}

Value *
BuildStringValue( void )
{
  Value * value = malloc( sizeof( Value * ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( Type ) );
  if( value->data == NULL )
    return NULL;
  
  value->profile = FindValueProfileByName( "string" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->c_p = "Test String Value";
  
  return value;
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
  
  Status * status = AppendStringToValueList( values, "First\n" );
  if( status != NULL )
    return NULL;
  
  status = AppendStringToValueList( values, "Second\n" );
  if( status != NULL )
    return NULL;
  
  status = AppendStringToValueList( values, "Third" );
  if( status != NULL )
    return NULL;
  
  output->data = malloc( sizeof( Type ) );
  if( output->data == NULL )
    return NULL;
  
  output->data->v_p = ( void * ) values;
  
  return output;
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
  
  value->data = malloc( sizeof( Type ) );
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
  
  value->data = malloc( sizeof( Type ) );
  if( value->data == NULL )
    return NULL;
  value->data->u_s = 65000u;
  
  return value;
}

ValueList *
BuildValueList( void )
{
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;
  
  Status * status;
  Value * value;
  
  value = BuildIntArrayValue();
  if( value == NULL )
    return NULL;
  status = AppendValueToValueList( list, value );
  if( status != NULL )
    return NULL;
  
  value = BuildUnsignedIntValue();
  if( value == NULL )
    return NULL;
  status = AppendValueToValueList( list, value );
  if( status != NULL )
    return NULL;
  
  value = BuildUnsignedShortValue();
  if( value == NULL )
    return NULL;
  status = AppendValueToValueList( list, value );
  if( status != NULL )
    return NULL;
  
  value = BuildCharArrayValue();
  if( value == NULL )
    return NULL;
  status = AppendValueToValueList( list, value );
  if( status != NULL )
    return NULL;
  
  value = BuildVoidValue();
  if( value == NULL )
    return NULL;
  status = AppendValueToValueList( list, value );
  if( status != NULL )
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
  
  value->data = malloc( sizeof( Type ) );
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
