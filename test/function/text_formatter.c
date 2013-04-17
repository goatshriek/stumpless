#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_entry_formatter( void );
const char * test_entry_attribute_formatter( void );
const char * test_entry_attribute_list_formatter( void );
const char * test_entry_summary_formatter( void );
const char * test_event_attribute_formatter( void );
const char * test_event_formatter( void );
const char * test_event_summary_formatter( void );
const char * test_level_formatter( void );
const char * test_value_formatter( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( entry_formatter )
  RUN_TEST( entry_attribute_formatter )
  RUN_TEST( entry_attribute_list_formatter )
  RUN_TEST( entry_summary_formatter )
  RUN_TEST( event_attribute_formatter )
  RUN_TEST( event_formatter )
  RUN_TEST( event_summary_formatter )
  RUN_TEST( level_formatter )
  RUN_TEST( value_formatter )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

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
  
  event = BuildEvent();
  if( event == NULL )
    return "could not build the test event";
  
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "a full event could not be formatted";
  if( strcmp( str, "Test Event (Test Level: level 42): Test Attribute 0: default value, attribute: 37, Test Attribute 2, attribute" ) != 0 )
    return "a full event was not properly formatted";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event without a name could not be formatted";
  if( strcmp( str, "event (Test Level: level 42): Test Attribute 0: default value, attribute: 37, Test Attribute 2, attribute" ) != 0 )
    return "an event without a name was not formatted correctly";
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event with only an attribute list could not be formatted";
  if( strcmp( str, "event: Test Attribute 0: default value, attribute: 37, Test Attribute 2, attribute" ) != 0 )
    return "an event with only an attribute list was not formatted correctly";
  
  event->name = "Test Event";
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event without a level could not be formatted";
  if( strcmp( str, "Test Event: Test Attribute 0: default value, attribute: 37, Test Attribute 2, attribute" ) != 0 )
    return "an event without a level was not formatted correctly";
  
  event->attributes = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event with only a name could not be formatted";
  if( strcmp( str, "Test Event" ) != 0 )
    return "an event with only a name was not formatted correctly";
  
  event->level = BuildLevel();
  if( event->level == NULL )
    return "could not build the test level";
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event without an attribute list could not be formatted";
  if( strcmp( str, "Test Event (Test Level: level 42)" ) != 0 )
    return "an event without an attribute list was not formatted correctly";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an event with only a level could not be formatted";
  if( strcmp( str, "event (Test Level: level 42)" ) != 0 )
    return "an event without a level was not formatted correctly";
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "an empty event could not be formatted";
  if( strcmp( str, "event" ) != 0 )
    return "an empty event was not formatted correctly";
  
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
  if( output == NULL )
    return "an event without a name could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "event (Test Level: level 42)" ) != 0 )
    return "an event without a name was not formatted correctly";
  
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
  char * str;
  
  output = StumplessLevelAsText( level );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  level = BuildLevel();
  if( level == NULL )
    return "could not build the test level";
  
  output = StumplessLevelAsText( level );
  if( output == NULL )
    return "a full level could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "Test Level: level 42" ) != 0 )
    return "a full level was not formatted correctly";
  
  level->name = NULL;
  output = StumplessLevelAsText( level );
  if( output == NULL )
    return "a level with no name could not be formatted";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "level 42" ) != 0 )
    return "a level with no name was not formatted correctly";
  
  return NULL;
}

const char *
test_value_formatter( void )
{
  StumplessValue * value = NULL;
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessValueAsText( value );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  value = BuildUnsignedShortValue();
  if( value == NULL )
    return "could not build test unsigned short value";
  output = StumplessValueAsText( value );
  if( output == NULL )
    return "the output was null for a valid value";
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have the correct type";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "65000 (unsigned short)" ) != 0 )
    return "an unsigned int value was not formatted correctly";
  
  value = BuildIntArrayValue();
  if( value == NULL )
    return "could not build test array value";
  output = StumplessValueAsText( value );
  if( output == NULL )
    return "could not format an array value";
  str = StumplessFormattedOutputToString( output );
  if( strcmp( str, "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] (int)" ) != 0 )
    return "an array value was not formatted correctly";
  
  return NULL;
}
