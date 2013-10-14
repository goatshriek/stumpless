#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/output.h"
#include "private/text_formatter.h"
#include "private/type.h"
#include "private/value_constructor.h"

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
  RUN_TEST( value_list_all_strings )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_entry_formatter( void )
{
  Entry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build the test entry" )
  
  Output * output;
  char * str;
  
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "a full entry could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for a full entry" )
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "a full entry was not properly formatted" )
  
  entry->description = NULL;
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry without a description was not formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without a description" )
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry without a description was not properly formatted" )
  
  entry->event = NULL;
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only attributes was not formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only attributes" )
  ASSERT_STRINGS_EQUAL( "entry: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry with only attributes was not properly formatted" )
  
  entry->description = "Test Entry";
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry without an event could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without an event" )
  ASSERT_STRINGS_EQUAL( "Test Entry: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an entry without an event was not properly formatted" )
  
  entry->attributes = NULL;
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only a description could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only a description" )
  ASSERT_STRINGS_EQUAL( "Test Entry", str,
                        "an entry with only a description was not properly formatted" )
  
  entry->event = BuildEvent();
  FAIL_IF_NULL( entry->event, "could not build the test event" )
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry without attributes could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry without attributes" )
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]", str,
                        "an entry without attributes was not properly formatted" )
  
  entry->description = NULL;
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an entry with only an event could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an entry with only an event" )
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]", str,
                        "an entry with only an event was not properly formatted" )
  
  entry->event = NULL;
  output = EntryToText( entry );
  FAIL_IF_NULL( output, "an empty entry could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an empty entry" )
  ASSERT_STRINGS_EQUAL( "entry", str,
                        "an empty entry did not return the proper output" )
  
  return NULL;
}

const char *
test_entry_attribute_formatter( void )
{
  EntryAttribute * attribute = BuildEntryAttribute();
  FAIL_IF_NULL( attribute, "could not build the test entry attribute" )
  
  Output * output;
  output = EntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "a full entry attribute could not be formatted" )
  char * str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Value (string)", str,
                        "a full entry attribute was not formatted correctly" )
  
  attribute->value = NULL;
  output = EntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute without a set value could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Default Value (string)",
                        str,
                        "an attribute without a set value was not formatted correctly" )
  
  attribute->event_attribute->name = NULL;
  output = EntryAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute with a default value was not formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute: Test Default Value (string)", str,
                        "an attribute with a default value was not formatted correctly" )
  
  attribute->event_attribute->default_value = NULL;
  output = EntryAttributeToText( attribute );
  FAIL_IF_NOT_NULL( output, "an attribute with no value was not empty" )
  
  return NULL;
}

const char *
test_entry_attribute_list_formatter( void )
{
  Entry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build the test entry" )
  
  char * str;
  Output * output;
  output = EntryAttributeListToText( entry );
  FAIL_IF_NULL( output, "the output could not be created" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "the list was not formatted correctly" )
  
  return NULL;
}

const char *
test_entry_summary_formatter( void )
{
  Entry * entry = BuildEntry();
  FAIL_IF_NULL( entry, "could not build test entry" )
  
  Output * output;
  char * str;
  
  output = EntrySummaryToText( entry );
  FAIL_IF_NULL( output, "a full entry could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Entry [Test Event (Test Level: level 42)]", str,
                        "a full entry was not properly formatted" )
  
  entry->description = NULL;
  output = EntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an entry without a description could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "entry [Test Event (Test Level: level 42)]", str,
                        "an entry without a description was not properly formatted" )
  
  entry->event = NULL;
  output = EntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an empty entry could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "entry", str,
                        "an empty entry was not properly formatted" )
  
  entry->description = "Test Entry";
  output = EntrySummaryToText( entry );
  FAIL_IF_NULL( output, "an entry without an event could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Entry", str,
                        "an entry without an event was not properly formatted" )
  
  return NULL;
}

const char *
test_event_attribute_formatter( void )
{
  Output * output;
  EventAttribute * attribute;
  char * str;
  
  attribute = malloc( sizeof( EventAttribute ) );
  FAIL_IF_NULL( attribute, "the test attribute could not be created" )
  
  output = EventAttributeToText( NULL );
  FAIL_IF_NOT_NULL( output,
                    "an empty attribute did not generate the appropriate error" )
  
  attribute->name = NULL;
  attribute->default_value = NULL;
  
  output = EventAttributeToText( attribute );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute", str,
                        "an empty attribute did not generate correct string" )
  
  attribute->name = "Test Attribute";
  output = EventAttributeToText( attribute );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( attribute->name, str,
                        "an attribute with only a name was not formatted correctly" )
  
  attribute->default_value = ValueFromString( "default value" );
  output = EventAttributeToText( attribute );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Attribute: default value (string)", str,
                        "a full attribute was not formatted correctly" )
  
  attribute->name = NULL;
  output = EventAttributeToText( attribute );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute: default value (string)", str,
                        "an attribute with only a default value was not formatted correctly" )
  
  return NULL;
}

const char *
test_event_attribute_list_formatter( void )
{
  Event * event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  Output * output;
  output = EventAttributeListToText( NULL );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null event" )
  
  output = EventAttributeListToText( event );
  FAIL_IF_NULL( output, "a null output was created for a non null event" )
  
  return NULL;
}

const char *
test_event_formatter( void )
{
  Event * event = NULL;
  Output * output;
  char * str;

  output = EventToText( event );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null pointer" )
  
  event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  output = EventToText( event );
  FAIL_IF_NULL( output, "a full event could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string" )
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42): Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "a full event was not properly formatted" )
  
  event->name = NULL;
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event without a name could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42): Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event without a name was not formatted correctly" )
  
  event->level = NULL;
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event with only an attribute list could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event: Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event with only an attribute list was not formatted correctly" )
  
  event->name = "Test Event";
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event without a level could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event: Test Attribute 0: default value (string), attribute: 37 (unsigned int), Test Attribute 2, attribute",
                        str,
                        "an event without a level was not formatted correctly" )
  
  event->attributes = NULL;
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event with only a name could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event", str,
                        "an event with only a name was not formatted correctly" )
  
  event->level = BuildLevel();
  FAIL_IF_NULL( event->level, "could not build the test level" )
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event without an attribute list could not be formatted" )
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42)", str,
                        "an event without an attribute list was not formatted correctly" )
  
  event->name = NULL;
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an event with only a level could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42)", str,
                        "an event without a level was not formatted correctly" )
  
  event->level = NULL;
  str = OutputToString( EventToText( event ) );
  FAIL_IF_NULL( str, "an empty event could not be formatted" )
  ASSERT_STRINGS_EQUAL( "event", str,
                        "an empty event was not formatted correctly" )
  
  return NULL;
}

const char *
test_event_summary_formatter( void )
{
  Output * output;
  char * str;
  
  output = EventSummaryToText( NULL );
  FAIL_IF_NOT_NULL( output, "a null event did not return null output" )
  
  Event * event = BuildEvent();
  FAIL_IF_NULL( event, "could not build the test event" )
  
  output = EventSummaryToText( event );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event (Test Level: level 42)", str,
                        "a full event did not generate the correct summary" )
  
  event->name = NULL;
  output = EventSummaryToText( event );
  FAIL_IF_NULL( output, "an event without a name could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "event (Test Level: level 42)", str,
                        "an event without a name was not formatted correctly" )
  
  event->level = NULL;
  output = EventSummaryToText( event );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "event", str,
                        "an empty event did not generate the correct summary" )
  
  event->name = "Test Event";
  output = EventSummaryToText( event );
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event", str,
                        "an event without a level did not generate the correct summary" )
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  Output * output = LevelToText( NULL );
  FAIL_IF_NOT_NULL( output, "the output was not null for a null pointer" )
  
  Level * level = BuildLevel();
  FAIL_IF_NULL( level, "could not build the test level" )
  
  output = LevelToText( level );
  FAIL_IF_NULL( output, "a full level could not be formatted" )
  char * str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Level: level 42", str,
                        "a full level was not formatted correctly" )
  
  level->name = NULL;
  output = LevelToText( level );
  FAIL_IF_NULL( output, "a level with no name could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "level 42", str,
                        "a level with no name was not formatted correctly" )
  
  return NULL;
}

const char *
test_value_list_all_strings( void )
{
  Entry * entry = BuildEntry();
  if( entry == NULL )
    return "could not build test entry";
  
  Output * output = EntryToText( entry );
  if( output == NULL || output->data == NULL )
    return "the output could not be built";
  
  if( strcmp( output->profile->name, "text" ) != 0 )
    return "the created output did not have a text format";
  
  ValueList * list = ( ValueList * ) output->data->v_p;
  if( list == NULL )
    return "the output did not have a value list";
  
  ValueListNode * node = list->first;
  while( node != NULL ){
    printf( "\n%s\n", node->value->profile->name );
    if( strcmp( node->value->profile->name, "string" ) != 0 )
      return "there was a non-string value in the list";
    
    node = node->next;
  }
  
  return NULL;
}
