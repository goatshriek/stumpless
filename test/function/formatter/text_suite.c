#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/formatter/text.h>
#include <stumpless/value/constructor.h>

#include "private/output.h"
#include "private/formatter.h"
#include "private/container/list/value.h"
#include "private/container/list/iterator/value.h"
#include "test/function/formatter/text_suite.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Event )
  TEST( EventAttribute )
  TEST( EventAttributes)
  TEST( Initializer )
  TEST( Level )
  TEST( Record )
  TEST( RecordAttribute )
  TEST( RecordAttributes )
  TEST( Value )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestEvent
( void )
{
  char *str;
  Event *event;
  Formatter *formatter;
  Output *output;

  if( EventToText( NULL, NULL ) )
    return "a NULL Formatter and Event returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventToText( formatter, NULL ) )
    return "a NULL Event returned an Output";

  event = BuildEvent();
  if( !event )
    return "could not build a test Event";

  if( EventToText( NULL, event ) )
    return "a NULL Formatter returned an Output";

  output = EventToText( formatter, event );
  if( !output )
    return "an Event could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event [Test Level (42.31.7)] - Test Attribute 1 [default value], Test Attribute 2, Unused Attribute", str, "a full Event was not properly formatted" )

  return NULL;
}

const char *
TestEventAttribute
( void )
{
  char *str;
  EventAttribute *attribute;
  Formatter *formatter;
  Output *output;

  if( EventAttributeToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventAttributeToText( formatter, NULL ) )
    return "a NULL attribute returned an Output";

  attribute = BuildEventAttribute();
  if( !attribute )
    return "could not build a test attribute";

  if( EventAttributeToText( NULL, attribute ) )
    return "a NULL Formatter returned an output";

  output = EventAttributeToText( formatter, attribute );
  if( !output )
    return "an attribute could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event Attribute [Test Default Value]", str, "the attribute was not formatted properly" )

  return NULL;
}

const char *
TestEventAttributes
( void )
{
  char *str;
  Dictionary *attributes;
  Formatter *formatter;
  Output *output;

  if( EventAttributesToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventAttributesToText( formatter, NULL ) )
    return "a NULL Dictionary returned an Output";

  attributes = BuildDictionaryOfEventAttributes();
  if( !attributes )
    return "could not build a test attribute Dictionary";

  if( EventAttributesToText( NULL, attributes ) )
    return "a NULL Formatter returned an output";

  output = EventAttributesToText( formatter, attributes );
  if( !output )
    return "a Dictionary of attributes could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Attribute 1 [default value], Test Attribute 2, Unused Attribute", str, "the attributes were not properly formatted" )

  return NULL;
}

const char *
TestInitializer
( void )
{
  Formatter *text_formatter;

  text_formatter = FindFormatterByName( "text" );
  if( !text_formatter )
    return "the text Formatter could not be found";

  ASSERT_STRINGS_EQUAL( "text", text_formatter->name, "the text Formatter did not have the correct name" )
  if( text_formatter->format != RecordToText )
    return "the text Formatter did not have the correct format function";

  return NULL;
}

const char *
TestLevel
( void )
{
  char *str;
  Formatter *formatter;
  Level *level;
  Output *result;

  if( LevelToText( NULL, NULL ) )
    return "a NULL Formatter and Level returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "could not find text Formatter";

  if( LevelToText( formatter, NULL ) )
    return "a NULL Level returned an Output";

  level = BuildLevel();
  if( !level )
    return "could not build a test Level";

  if( LevelToText( NULL, level ) )
    return "a NULL Formatter returned an Output";

  result = LevelToText( formatter, level );
  if( !result )
    return "a Level could not be formatted";

  str = OutputToString( result );
  if( !str )
    return "the Output could not be converted to a string";
  ASSERT_STRINGS_EQUAL( "Test Level (42.31.7)", str, "a complete Level was not formatted correctly" )

  return NULL;
}

const char *
TestRecord
( void )
{
  char *str;
  Formatter *formatter;
  Record *record;
  Output *output;

  if( RecordToText( NULL, NULL ) )
    return "a NULL Formatter and Record returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordToText( formatter, NULL ) )
    return "a NULL Record returned an Output";

  record = BuildRecord();
  if( !record )
    return "could not build a test Record";

  if( RecordToText( NULL, record ) )
    return "a NULL Formatter returned an Output";

  output = RecordToText( formatter, record );
  if( !output )
    return "a Record could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event [Test Level (42.31.7)] - Anonymous Attribute: anonymous attribute value, Test Attribute 1: default value, Test Attribute 2: attribute value", str, "a full Event was not properly formatted" )

  return NULL;
}

const char *
TestRecordAttribute
( void )
{
  char *str;
  Formatter *formatter;
  RecordAttribute *attribute;
  Output *output;

  if( RecordAttributeToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordAttributeToText( formatter, NULL ) )
    return "a NULL attribute returned an Output";

  attribute = BuildRecordAttribute();
  if( !attribute )
    return "could not build a test attribute";

  if( RecordAttributeToText( NULL, attribute ) )
    return "a NULL Formatter returned an output";

  output = RecordAttributeToText( formatter, attribute );
  if( !output )
    return "a full attribute could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the full Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Value", str, "a full attribute was not formatted properly" )

  attribute->value = NULL;
  output = RecordAttributeToText( formatter, attribute );
  if( !output )
    return "a default value attribute could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the default Value Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event Attribute: Test Default Value", str, "a default value attribute was not formatted properly" )

  return NULL;
}

const char *
TestRecordAttributes
( void )
{
  char *str;
  Dictionary *attributes;
  Formatter *formatter;
  Output *output;

  if( RecordAttributesToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordAttributesToText( formatter, NULL ) )
    return "a NULL Dictionary returned an Output";

  attributes = BuildDictionaryOfRecordAttributes();
  if( !attributes )
    return "could not build a test attribute Dictionary";

  if( RecordAttributesToText( NULL, attributes ) )
    return "a NULL Formatter returned an output";

  output = RecordAttributesToText( formatter, attributes );
  if( !output )
    return "a Dictionary of attributes could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Anonymous Attribute: anonymous attribute value, Test Attribute 1: default value, Test Attribute 2: attribute value", str, "the attributes were not properly formatted" )

  return NULL;
}

const char *
TestValue
( void )
{
  char *str;
  Formatter *formatter;
  Output *output;
  Value *value;

  if( ValueToText( NULL, NULL ) )
    return "a NULL Formatter and Value returned an Output";

  formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( ValueToText( formatter, NULL ) )
    return "a NULL Value returned an Output";

  value = BuildValue();
  if( !value )
    return "could not build a test Value";

  if( ValueToText( NULL, value ) )
    return "a NULL Formatter returned an output";

  output = ValueToText( formatter, value );
  if( !output )
    return "a Value could not be formatted";

  str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "6500", str, "the attributes were not properly formatted" )

  return NULL;
}
