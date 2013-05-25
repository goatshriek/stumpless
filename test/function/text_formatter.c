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
const char * test_event_attribute_list_formatter( void );
const char * test_event_formatter( void );
const char * test_event_summary_formatter( void );
const char * test_level_formatter( void );
const char * test_value_formatter( void );
const char * test_value_list_all_strings( void );

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
  RUN_TEST( event_attribute_list_formatter )
  RUN_TEST( event_formatter )
  RUN_TEST( event_summary_formatter )
  RUN_TEST( level_formatter )
  RUN_TEST( value_formatter )
  RUN_TEST( value_list_all_strings )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_entry_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build the test entry" )
  
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "a full entry could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for a full entry" )
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "a full entry was not properly formatted" )
  
  entry->description = NULL;
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry without a description was not formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without a description" )
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry without a description was not properly formatted" )
  
  entry->event = NULL;
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only attributes was not formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only attributes" )
  ASSERT_STRINGS_EQUAL( "entry: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry with only attributes was not properly formatted" )
  
  entry->description = "Test Entry";
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry without an event could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without an event" )
  ASSERT_STRINGS_EQUAL( "Test Entry: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry without an event was not properly formatted" )
  
  entry->attributes = NULL;
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only a description could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only a description" )
  ASSERT_STRINGS_EQUAL( "Test Entry", str,
                        "an entry with only a description was not properly formatted" )
  
  entry->event = BuildEvent();
  FAIL_IF_NULL( entry->event, "could not build the test event" )
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry without attributes could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without attributes" )
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]", str,
                        "an entry without attributes was not properly formatted" )
  
  entry->description = NULL;
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only an event could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only an event" )
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]", str,
                        "an entry with only an event was not properly formatted" )
  
  entry->event = NULL;
  output = StumplessEntryToText( entry );
  FAIL_IF_NULL( output, "an empty entry could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an empty entry" )
  ASSERT_STRINGS_EQUAL( "entry", str,
                        "an empty entry did not return the proper output" )
  
  return NULL;
}

const char *
test_entry_attribute_formatter( void )
{
  StumplessEntryAttribute * attribute = BuildEntryAttribute();
  FAIL_IF_NULL( attribute, "could not build the test entry attribute" )
  
  StumplessFormattedOutput * output;
  output = StumplessEntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "a full entry attribute could not be formatted" )
  char * str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Value (string)", str,
                        "a full entry attribute was not formatted correctly" )
  
  attribute->value = NULL;
  output = StumplessEntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute without a set value could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Default Value (string)",
                        str,
                        "an attribute without a set value was not formatted correctly" )
  
  attribute->event_attribute->name = NULL;
  output = StumplessEntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute with a default value was not formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute: Test Default Value (string)", str,
                        "an attribute with a default value was not formatted correctly" )
  
  attribute->event_attribute->default_value = NULL;
  output = StumplessEntryAttributeToText( attribute );
  FAIL_IF_NOT_NULL( output, "an attribute with no value was not empty" )
  
  return NULL;
}

const char *
test_entry_attribute_list_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build the test entry" )
  
  char * str;
  StumplessFormattedOutput * output;
  output = StumplessEntryAttributeListToText( entry );
  FAIL_IF_NULL( output, "the output could not be created" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "the list was not formatted correctly" )
  
  return NULL;
}

const char *
test_entry_summary_formatter( void )
{
  StumplessEntry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build test entry" )
  
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEntrySummaryToText( entry );
  FAIL_IF_NULL( output, "a full entry could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]", str,
                        "a full entry was not properly formatted" )
  
  entry->description = NULL;
  output = StumplessEntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an entry without a description could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]", str,
                        "an entry without a description was not properly formatted" )
  
  entry->event = NULL;
  output = StumplessEntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an empty entry could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "entry", str,
                        "an empty entry was not properly formatted" )
  
  entry->description = "Test Entry";
  output = StumplessEntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an entry without an event could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Entry", str,
                        "an entry without an event was not properly formatted" )
  
  return NULL;
}

const char *
test_event_attribute_formatter( void )
{
  StumplessFormattedOutput * output;
  StumplessEventAttribute * attribute;
  char * str;
  
  attribute = malloc( sizeof( StumplessEventAttribute ) );
  FAIL_IF_NULL( attribute, "the test attribute could not be created" )
  
  output = StumplessEventAttributeToText( NULL );
  FAIL_IF_NOT_NULL( output,
                    "an empty attribute did not generate the appropriate error" )
  
  attribute->name = NULL;
  attribute->default_value = NULL;
  
  output = StumplessEventAttributeToText( attribute );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute", str,
                        "an empty attribute did not generate correct string" )
  
  attribute->name = "Test Attribute";
  output = StumplessEventAttributeToText( attribute );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( attribute->name, str,
                        "an attribute with only a name was not formatted correctly" )
  
  attribute->default_value = StumplessValueFromString( "default value" );
  output = StumplessEventAttributeToText( attribute );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Attribute: default value (string)", str,
                        "a full attribute was not formatted correctly" )
  
  attribute->name = NULL;
  output = StumplessEventAttributeToText( attribute );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute: default value (string)", str,
                        "an attribute with only a default value was not formatted correctly" )
  
  return NULL;
}

const char *
test_event_attribute_list_formatter( void )
{
  StumplessEvent * event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  StumplessFormattedOutput * output;
  output = StumplessEventAttributeListToText( NULL );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null event" )
  
  output = StumplessEventAttributeListToText( event );
  FAIL_IF_NULL( output, "a null output was created for a non null event" )
  
  return NULL;
}

const char *
test_event_formatter( void )
{
  StumplessEvent * event = NULL;
  StumplessFormattedOutput * output;
  char * str;

  output = StumplessEventToText( event );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null pointer" )
  
  event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  output = StumplessEventToText( event );
  FAIL_IF_NULL( output, "a full event could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string" )
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42): Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "a full event was not properly formatted" )
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event without a name could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42): Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event without a name was not formatted correctly" )
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event with only an attribute list could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event: Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event with only an attribute list was not formatted correctly" )
  
  event->name = "Test Event";
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event without a level could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event: Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event without a level was not formatted correctly" )
  
  event->attributes = NULL;
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event with only a name could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event", str,
                        "an event with only a name was not formatted correctly" )
  
  event->level = BuildLevel();
  FAIL_IF_NULL( event->level, "could not build the test level" )
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event without an attribute list could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42)", str,
                        "an event without an attribute list was not formatted correctly" )
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an event with only a level could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42)", str,
                        "an event without a level was not formatted correctly" )
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventToText( event ) );
  FAIL_IF_NULL( str, "an empty event could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event", str,
                        "an empty event was not formatted correctly" )
  
  return NULL;
}

const char *
test_event_summary_formatter( void )
{
  StumplessFormattedOutput * output;
  char * str;
  
  output = StumplessEventSummaryToText( NULL );
  FAIL_IF_NOT_NULL( output, "a null event did not return null output" )
  
  StumplessEvent * event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  output = StumplessEventSummaryToText( event );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42)", str,
                        "a full event did not generate the correct summary" )
  
  event->name = NULL;
  output = StumplessEventSummaryToText( event );
  FAIL_IF_NULL( output, "an event without a name could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42)", str,
                        "an event without a name was not formatted correctly" )
  
  event->level = NULL;
  output = StumplessEventSummaryToText( event );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "event", str,
                        "an empty event did not generate the correct summary" )
  
  event->name = "Test Event";
  output = StumplessEventSummaryToText( event );
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event", str,
                        "an event without a level did not generate the correct summary" )
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  StumplessFormattedOutput * output = StumplessLevelToText( NULL );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null pointer" )
  
  StumplessLevel * level = BuildLevel();
  FAIL_IF_NULL( level, "could not build the test level" )
  
  output = StumplessLevelToText( level );
  FAIL_IF_NULL( output, "a full level could not be formatted" )
  char * str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Level: level 42", str,
                        "a full level was not formatted correctly" )
  
  level->name = NULL;
  output = StumplessLevelToText( level );
  FAIL_IF_NULL( output, "a level with no name could not be formatted" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "level 42", str,
                        "a level with no name was not formatted correctly" )
  
  return NULL;
}

const char *
test_value_formatter( void )
{
  StumplessFormattedOutput * output = StumplessValueToText( NULL );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null pointer" )
  
  StumplessValue * value = BuildUnsignedShortValue();
  FAIL_IF_NULL( value, "could not build test unsigned short value" )
  output = StumplessValueToText( value );
  FAIL_IF_NULL( output, "the output was null for a valid value" )
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have the correct type";
  char * str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "65000 (unsigned short)", str,
                        "an unsigned short value was not formatted correctly" )
  
  value = BuildIntArrayValue();
  FAIL_IF_NULL( value, "could not build test array value" )
  output = StumplessValueToText( value );
  FAIL_IF_NULL( output, "could not format an array value" )
  str = StumplessFormattedOutputToString( output );
  ASSERT_STRINGS_EQUAL( "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] (int array)", str,
                        "an array value was not formatted correctly" )
  
  return NULL;
}

const char *
test_value_list_all_strings( void )
{
  StumplessEntry * entry = BuildEntry();
  if( entry == NULL )
    return "could not build test entry";
  
  StumplessFormattedOutput * output = StumplessEntryToText( entry );
  if( output == NULL || output->payload == NULL )
    return "the output could not be built";
  
  if( output->format != STUMPLESS_TEXT )
    return "the created output did not have a text format";
  
  StumplessValueList * list = output->payload->values;
  if( list == NULL )
    return "the output did not have a value list";
  
  StumplessValueListNode * node = list->first;
  while( node != NULL ){
    printf( "\n%s\n", node->value->profile->name );
    if( strcmp( node->value->profile->name, "String" ) != 0 )
      return "there was a non-string value in the list";
    
    node = node->next;
  }
  
  return NULL;
}
