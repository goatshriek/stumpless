#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "builder.h"

const char * test_entry_formatter( void );
const char * test_entry_attribute_formatter( void );
const char * test_entry_attribute_list_formatter( void );
const char * test_entry_summary_formatter( void );
const char * test_event_attribute_formatter( void );
const char * test_event_formatter( void );
const char * test_event_summary_formatter( void );
const char * test_level_formatter( void );
const char * test_value_formatter( void );

StumplessEventAttribute ** GetTestEventAttributeList( void );
StumplessLevel * GetTestLevel( void );
StumplessValue * GetTestValueUnsignedShort( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_entry_formatter();
  if( result != NULL ){
    printf( "Entry Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_entry_attribute_formatter();
  if( result != NULL ){
    printf( "Entry Attribute Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_entry_attribute_list_formatter();
  if( result != NULL ){
    printf( "Entry Attribute List Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_entry_summary_formatter();
  if( result != NULL ){
    printf( "Entry Summary Formatter Test Failed: %s\n", result );
    failure_count++;
  }
   
  result = test_event_attribute_formatter();
  if( result != NULL ){
    printf( "Event Attribute Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_event_formatter();
  if( result != NULL ){
    printf( "Event Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_event_summary_formatter();
  if( result != NULL ){
    printf( "Event Summary Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_level_formatter();
  if( result != NULL ){
    printf( "Level Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_value_formatter();
  if( result != NULL ){
    printf( "Event Attribute Value Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

// todo see if a backslash can clean up the formatting in this test
const char *
test_entry_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  if( entry == NULL )
    return "could not build the test entry";
  
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "a full entry could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value, attribute: not 37, attribute: unnamed value, attribute: no event attribute" ) != 0 )
    return "a full entry was not properly formatted";
  
  entry->description = NULL;
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry without a description could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value, attribute: not 37, attribute: unnamed value, attribute: no event attribute" ) != 0 )
    return "an entry without a description was not properly formatted";
  
  entry->event = NULL;
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry with only attributes could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry: Test Attribute 0: default value, attribute: not 37, attribute: unnamed value, attribute: no event attribute" ) != 0 )
    return "an entry with only attributes was not properly formatted";
  
  entry->description = "Test Entry";
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry without an event could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Entry: Test Attribute 0: default value, attribute: not 37, attribute: unnamed value, attribute: no event attribute" ) != 0 )
    return "an entry without an event was not properly formatted";
  
  entry->attributes = NULL;
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry with only a description could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Entry" ) != 0 )
    return "an entry with only a description was not properly formatted";
  
  entry->event = BuildEvent();
  if( entry->event == NULL )
    return "could not build the test event";
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry without attributes could not be formatted";
  str = StumplessFormattedOutputToString( output );
  printf( "%s\n", str );
  if( strcmp( str, "Test Entry [Test Event (Test Level: level 42)]" ) != 0 )
    return "an entry without attributes was not properly formatted";
  
  entry->description = NULL;
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an entry with only an event could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry [Test Event (Test Level: level 42)]" ) != 0 )
    return "an entry with only an event was not properly formatted";
  
  entry->event = NULL;
  output = StumplessEntryAsText( entry );
  if( output == NULL )
    return "an empty entry could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry" ) != 0 )
    return "an empty entry did not return the proper output";
  
  return NULL;
}

const char *
test_entry_attribute_formatter( void )
{
  StumplessEntryAttribute * attribute = BuildEntryAttribute();
  if( attribute == NULL )
    return "could not build the test entry attribute";
  
  StumplessFormattedOutput * output;
  output = StumplessEntryAttributeAsText( attribute );
  if( output == NULL )
    return "a full entry attribute could not be formatted";
  char * str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Event Attribute: Test Value" ) != 0 )
    return "a full entry attribute was not formatted correctly";
  
  attribute->value = NULL;
  output = StumplessEntryAttributeAsText( attribute );
  if( output == NULL )
    return "an attribute without a set value could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Event Attribute: Test Default Value" ) != 0 )
    return "an attribute without a set value was not formatted correctly";
  
  attribute->event_attribute->name = NULL;
  output = StumplessEntryAttributeAsText( attribute );
  if( output == NULL )
    return "an attribute with a default value was not formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "attribute: Test Default Value" ) != 0 )
    return "an attribute with a default value was not formatted correctly";
  
  attribute->event_attribute->default_value = NULL;
  output = StumplessEntryAttributeAsText( attribute );
  if( output != NULL )
    return "an attribute with no value was not empty";
  
  return NULL;
}

const char *
test_entry_attribute_list_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  if( entry == NULL )
    return "could not build the test entry";
  
  char * str;
  StumplessFormattedOutput * output;
  output = StumplessEntryAttributeListAsText( entry );
  if( output == NULL )
    return "the output could not be created";
  str = StumplessFormattedOutputToString( output );
  // todo see if a backslash can fix the formatting here
  if( strcmp( str, "Test Attribute 0: default value, attribute: not 37, attribute: unnamed value, attribute: no event attribute" ) != 0 )
    return "the list was not formatted correctly";
  
  return NULL;
}

const char *
test_entry_summary_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  if( entry == NULL )
    return "could not build test entry";
  
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEntrySummaryAsText( entry );
  if( output == NULL )
    return "a full entry could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Entry [Test Event (Test Level: level 42)]" ) != 0 )
    return "a full entry was not properly formatted";
  
  entry->description = NULL;
  output = StumplessEntrySummaryAsText( entry );
  if( output == NULL )
    return "an entry without a description could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry [Test Event (Test Level: level 42)]" ) != 0 )
    return "an entry without a description was not properly formatted";
  
  entry->event = NULL;
  output = StumplessEntrySummaryAsText( entry );
  if( output == NULL )
    return "an empty entry could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "entry" ) != 0 )
    return "an empty entry was not properly formatted";
  
  entry->description = "Test Entry";
  output = StumplessEntrySummaryAsText( entry );
  if( output == NULL )
    return "an entry without an event could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Entry" ) != 0 )
    return "an entry without an event was not properly formatted";
  
  return NULL;
}

const char *
test_event_attribute_formatter( void )
{
  StumplessFormattedOutput * output;
  StumplessEventAttribute * attribute;
  char * str;
  
  attribute = malloc( sizeof( StumplessEventAttribute ) );
  if( attribute == NULL )
    return "the test attribute could not be created";
  
  output = StumplessEventAttributeAsText( NULL );
  if( output != NULL )
    return "an empty attribute did not generate the appropriate error";
  
  attribute->name = NULL;
  attribute->default_value = NULL;
  
  output = StumplessEventAttributeAsText( attribute );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "attribute" ) != 0 )
    return "an empty attribute did not generate correct string";
  
  attribute->name = "Test Attribute";
  output = StumplessEventAttributeAsText( attribute );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, attribute->name ) != 0 )
    return "an attribute with only a name was not formatted correctly";
  
  attribute->default_value = StumplessValueFromString( "default value" );
  output = StumplessEventAttributeAsText( attribute );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Attribute: default value" ) != 0 )
    return "a full attribute was not formatted correctly";
  
  attribute->name = NULL;
  output = StumplessEventAttributeAsText( attribute );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "attribute: default value" ) != 0 )
    return "an attribute with only a default value was not formatted correctly";
  
  return NULL;
}

const char *
test_event_formatter( void )
{
  StumplessEvent * event = NULL;
  StumplessFormattedOutput * output;
  char * str;

  output = StumplessEventAsText( event );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  event = malloc( sizeof( StumplessEvent ) );
  if( event == NULL )
    return "the test event could not be created";
  
  event->name = NULL;
  event->level = NULL;
  event->attributes = NULL;
  event->attribute_count = 0;
  
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "event" ) != 0 )
    return "an empty event did not generate the correct string";
  
  // todo replace this usage with the builder module
  // creating the values to give the event for each test
  const char * name = "Test Event";
  StumplessLevel * level = GetTestLevel();
  if( level == NULL )
    return "the test level could not be created";
  StumplessEventAttribute ** list = GetTestEventAttributeList();
  if( list == NULL )
    return "the test event attribute list could not be created";
  
  event->name = name;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, name ) != 0 )
    return "an event with only a name was not formatted correctly";
  
  event->level = level;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event (Test Level: level 42)" ) != 0 )
    return "an event without a list was not formatted correctly";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Level: level 42 event" ) != 0 )
    return "an event with only a level was not formatted correctly";
  
  event->attributes = list;
  event->attribute_count = 3;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  // todo see if the formatting here can be fixed with a backslash
  if( strcmp( str, "Test Level: level 42 event: attr_0 name: val_0, attribute: val_1, attr_2 name" ) != 0 )
    return "an event without a name was not formatted correctly";
  
  event->name = name;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event (Test Level: level 42): attr_0 name: val_0, attribute: val_1, attr_2 name" ) != 0 )
    return "an event with all components was not formatted correctly";
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event: attr_0 name: val_0, attribute: val_1, attr_2 name" ) != 0 )
    return "an event without a level was not formatted correctly";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "event: attr_0 name: val_0, attribute: val_1, attr_2 name" ) != 0 )
    return "an event with only a list was not formatted correctly";
  
  return NULL;
}

const char *
test_event_summary_formatter( void )
{
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEventSummaryAsText( NULL );
  if( output != NULL )
    return "a null event did not return null output";
  
  StumplessEvent * event = BuildEvent();
  if( event == NULL )
    return "could not build the test event";
  
  output = StumplessEventSummaryAsText( event );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Event (Test Level: level 42)" ) != 0 )
    return "a full event did not generate the correct summary";
  
  event->name = NULL;
  output = StumplessEventSummaryAsText( event );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Level: level 42 event" ) != 0 )
    return "an event without a name did not generate the correct summary";
  
  event->level = NULL;
  output = StumplessEventSummaryAsText( event );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "event" ) != 0 )
    return "an empty event did not generate the correct summary";
  
  event->name = "Test Event";
  output = StumplessEventSummaryAsText( event );
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Event" ) != 0 )
    return "an event without a level did not generate the correct summary";
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  StumplessLevel * level = NULL;
  StumplessFormattedOutput * output;
  char * string_output;
  
  output = StumplessLevelAsText( level );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  level = malloc( sizeof( StumplessLevel ) );
  if( level == NULL )
    return "the test level could not be created";
  
  level->value = 30;
  level->name = NULL;
  output = StumplessLevelAsText( level );
  string_output = StumplessFormattedOutputToString( output );
  if( strcmp( string_output, "level 30" ) != 0 )
    return "the output was not correct for a level with no name";
  
  level->value = 67;
  level->name = "Test Level";
  output = StumplessLevelAsText( level );
  string_output = StumplessFormattedOutputToString( output );
  if( strcmp( string_output, "Test Level: level 67" ) != 0 )
    return "the output was not correct for a level with a name";
  
  return NULL;
}

const char *
test_value_formatter( void )
{
  StumplessValue * value = NULL;
  StumplessFormattedOutput * output;
  
  output = StumplessValueAsText( value );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  value = GetTestValueUnsignedShort();
  output = StumplessValueAsText( value );
  if( output == NULL )
    return "the output was null for a valid value";
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have the correct type";
  
  return NULL;
}

StumplessEventAttribute **
GetTestEventAttributeList( void )
{
  StumplessEventAttribute ** list;
  
  StumplessEventAttribute * attr_0 = malloc( sizeof( StumplessEventAttribute ));
  StumplessEventAttribute * attr_1 = malloc( sizeof( StumplessEventAttribute ));
  StumplessEventAttribute * attr_2 = malloc( sizeof( StumplessEventAttribute ));
  list = malloc( sizeof( StumplessEventAttribute * ) * 3 );
  if( attr_0 == NULL || attr_1 == NULL || attr_2 == NULL || list == NULL )
    return NULL;
  
  attr_0->name = "attr_0 name";
  attr_0->default_value = StumplessValueFromString( "val_0" );
  
  attr_1->name = NULL;
  attr_1->default_value = StumplessValueFromString( "val_1" );
  
  attr_2->name = "attr_2 name";
  attr_2->default_value = NULL;
  
  list[0] = attr_0;
  list[1] = attr_1;
  list[2] = attr_2;
  
  return list;
}

StumplessLevel *
GetTestLevel( void )
{
  StumplessLevel * level = malloc( sizeof( StumplessLevel ) );
  if( level == NULL )
    return NULL;
  
  level->value = 42;
  level->name = "Test Level";
  return level;
}

StumplessValue *
GetTestValueUnsignedShort( void )
{
  StumplessValue * value;
  
  value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->type = STUMPLESS_UNSIGNED_SHORT;
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->data->u_s = 3;
  value->length = 0;
  
  return value;
}
