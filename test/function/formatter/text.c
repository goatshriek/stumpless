#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/output.h"
#include "private/type.h"
#include "private/value/constructor.h"
#include "private/formatter/text.h"
#include "private/container/list/value.h"
#include "private/container/list/iterator/value.h"

#include "helper.h"

const char * test_record_formatter( void );
const char * test_record_attribute_formatter( void );
const char * test_record_attribute_list_formatter( void );
const char * test_record_summary_formatter( void );
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

  RUN_TEST( record_formatter )
  RUN_TEST( record_attribute_formatter )
  RUN_TEST( record_attribute_list_formatter )
  RUN_TEST( record_summary_formatter )
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
test_record_formatter( void )
{
  Record * record = BuildRecord();
  FAIL_IF_NULL( record, "could not build the test record" )

  Output * output;
  char * str;

  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "a full record could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for a full record" )
  ASSERT_STRINGS_EQUAL( "Test Record [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "a full record was not properly formatted" )

  record->description = NULL;
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record without a description was not formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record without a description" )
  ASSERT_STRINGS_EQUAL( "record [Test Event (Test Level: level 42)]: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an record without a description was not properly formatted" )

  record->event = NULL;
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record with only attributes was not formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record with only attributes" )
  ASSERT_STRINGS_EQUAL( "record: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an record with only attributes was not properly formatted" )

  record->description = "Test Record";
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record without an event could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record without an event" )
  ASSERT_STRINGS_EQUAL( "Test Record: Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "an record without an event was not properly formatted" )

  record->attributes = NULL;
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record with only a description could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record with only a description" )
  ASSERT_STRINGS_EQUAL( "Test Record", str,
                        "an record with only a description was not properly formatted" )

  record->event = BuildEvent();
  FAIL_IF_NULL( record->event, "could not build the test event" )
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record without attributes could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record without attributes" )
  ASSERT_STRINGS_EQUAL( "Test Record [Test Event (Test Level: level 42)]", str,
                        "an record without attributes was not properly formatted" )

  record->description = NULL;
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an record with only an event could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an record with only an event" )
  ASSERT_STRINGS_EQUAL( "record [Test Event (Test Level: level 42)]", str,
                        "an record with only an event was not properly formatted" )

  record->event = NULL;
  output = RecordToText( record, NULL );
  FAIL_IF_NULL( output, "an empty record could not be formatted" )
  str = OutputToString( output );
  FAIL_IF_NULL( str, "the output could not be converted to a string for an empty record" )
  ASSERT_STRINGS_EQUAL( "record", str,
                        "an empty record did not return the proper output" )

  return NULL;
}

const char *
test_record_attribute_formatter( void )
{
  RecordAttribute * attribute = BuildRecordAttribute();
  FAIL_IF_NULL( attribute, "could not build the test record attribute" )

  Output * output;
  output = RecordAttributeToText( attribute );
  FAIL_IF_NULL( output, "a full record attribute could not be formatted" )
  char * str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Value (string)", str,
                        "a full record attribute was not formatted correctly" )

  attribute->value = NULL;
  output = RecordAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute without a set value could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Default Value (string)",
                        str,
                        "an attribute without a set value was not formatted correctly" )

  EventAttribute *new_attribute = BuildEventAttribute();
  if( !new_attribute )
    return "could not build a test event attribute";
  attribute->event_attribute = new_attribute;

  new_attribute->name = NULL;
  output = RecordAttributeToText( attribute );
  FAIL_IF_NULL( output, "an attribute with a default value was not formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "attribute: Test Default Value (string)", str,
                        "an attribute with a default value was not formatted correctly" )

  new_attribute->default_value = NULL;
  output = RecordAttributeToText( attribute );
  FAIL_IF_NOT_NULL( output, "an attribute with no value was not empty" )

  return NULL;
}

const char *
test_record_attribute_list_formatter( void )
{
  Record * record = BuildRecord();
  FAIL_IF_NULL( record, "could not build the test record" )

  char * str;
  Output * output;
  output = RecordAttributeListToText( record );
  FAIL_IF_NULL( output, "the output could not be created" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Attribute 0: default value (string), attribute: not 37 (string), attribute: unnamed value (string), attribute: no event attribute (string)",
                        str,
                        "the list was not formatted correctly" )

  return NULL;
}

const char *
test_record_summary_formatter( void )
{
  Record * record = BuildRecord();
  FAIL_IF_NULL( record, "could not build test record" )

  Output * output;
  char * str;

  output = RecordSummaryToText( record );
  FAIL_IF_NULL( output, "a full record could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Record [Test Event (Test Level: level 42)]", str,
                        "a full record was not properly formatted" )

  record->description = NULL;
  output = RecordSummaryToText( record );
  FAIL_IF_NULL( output, "an record without a description could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "record [Test Event (Test Level: level 42)]", str,
                        "an record without a description was not properly formatted" )

  record->event = NULL;
  output = RecordSummaryToText( record );
  FAIL_IF_NULL( output, "an empty record could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "record", str,
                        "an empty record was not properly formatted" )

  record->description = "Test Record";
  output = RecordSummaryToText( record );
  FAIL_IF_NULL( output, "an record without an event could not be formatted" )
  str = OutputToString( output );
  ASSERT_STRINGS_EQUAL( "Test Record", str,
                        "an record without an event was not properly formatted" )

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
  Record * record = BuildRecord();
  if( !record )
    return "could not build test record";

  Output * output = RecordToText( record, NULL );
  if( !output || !output->data )
    return "the output could not be built";

  if( strcmp( output->profile->name, "text" ) != 0 )
    return "the created output did not have a text format";

  ValueList * list = ( ValueList * ) output->data->v_p;
  if( !list )
    return "the output did not have a value list";

  ValueListIterator * values = BeginValueList( list );
  Value * value;
  while( value = NextInValueListIterator( values ) ){
    printf( "\n%s\n", value->profile->name );
    if( strcmp( value->profile->name, "string" ) != 0 )
      return "there was a non-string value in the list";
  }
  DestroyValueListIterator( values );

  return NULL;
}
