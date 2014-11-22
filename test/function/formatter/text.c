#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/formatter/text.h>

#include "private/output.h"
#include "private/value/constructor.h"
#include "private/formatter.h"
#include "private/container/list/value.h"
#include "private/container/list/iterator/value.h"
#include "test/function/formatter/text.h"
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
  if( EventToText( NULL, NULL ) )
    return "a NULL Formatter and Event returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventToText( formatter, NULL ) )
    return "a NULL Event returned an Output";

  Event *event = BuildEvent();
  if( !event )
    return "could not build a test Event";

  if( EventToText( NULL, event ) )
    return "a NULL Formatter returned an Output";

  Output *output = EventToText( formatter, event );
  if( !output )
    return "an Event could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event [Test Level (42.31.7)] - Test Attribute 1 [default value], Test Attribute 2, Unused Attribute", str, "a full Event was not properly formatted" )

  return NULL;
}

const char *
TestEventAttribute
( void )
{
  if( EventAttributeToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventAttributeToText( formatter, NULL ) )
    return "a NULL attribute returned an Output";

  EventAttribute *attribute = BuildEventAttribute();
  if( !attribute )
    return "could not build a test attribute";

  if( EventAttributeToText( NULL, attribute ) )
    return "a NULL Formatter returned an output";

  Output *output = EventAttributeToText( formatter, attribute );
  if( !output )
    return "an attribute could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event Attribute [Test Default Value]", str, "the attribute was not formatted properly" )

  return NULL;
}

const char *
TestEventAttributes
( void )
{
  if( EventAttributesToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( EventAttributesToText( formatter, NULL ) )
    return "a NULL Dictionary returned an Output";

  Dictionary *attributes = BuildDictionaryOfEventAttributes();
  if( !attributes )
    return "could not build a test attribute Dictionary";

  if( EventAttributesToText( NULL, attributes ) )
    return "a NULL Formatter returned an output";

  Output *output = EventAttributesToText( formatter, attributes );
  if( !output )
    return "a Dictionary of attributes could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Attribute 1 [default value], Test Attribute 2", str, "the attributes were not properly formatted" )

  return NULL;
}

const char *
TestInitializer
( void )
{
  Formatter *text_formatter = FindFormatterByName( "text" );
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
  if( LevelToText( NULL, NULL ) )
    return "a NULL Formatter and Level returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "could not find text Formatter";

  if( LevelToText( formatter, NULL ) )
    return "a NULL Level returned an Output";

  Level *level = BuildLevel();
  if( !level )
    return "could not build a test Level";

  if( LevelToText( NULL, level ) )
    return "a NULL Formatter returned an Output";

  Output *result = LevelToText( formatter, level );
  if( !result )
    return "a Level could not be formatted";

  char *str = OutputToString( result );
  if( !str )
    return "the Output could not be converted to a string";
  ASSERT_STRINGS_EQUAL( "Test Level (42.31.7)", str, "a complete Level was not formatted correctly" )

  return NULL;
}

const char *
TestRecord
( void )
{
  if( RecordToText( NULL, NULL ) )
    return "a NULL Formatter and Record returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordToText( formatter, NULL ) )
    return "a NULL Record returned an Output";

  Record *record = BuildRecord();
  if( !record )
    return "could not build a test Record";

  if( RecordToText( NULL, record ) )
    return "a NULL Formatter returned an Output";

  Output *output = RecordToText( formatter, record );
  if( !output )
    return "a Record could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Test Event [Test Level (42.31.7)] - Anonymous Attribute: anonymous attribute value, Test Attribute 1: default value, Test Attribute 2: attribute value", str, "a full Event was not properly formatted" )

  return NULL;
}

const char *
TestRecordAttribute
( void )
{
  if( RecordAttributeToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordAttributeToText( formatter, NULL ) )
    return "a NULL attribute returned an Output";

  RecordAttribute *attribute = BuildRecordAttribute();
  if( !attribute )
    return "could not build a test attribute";

  if( RecordAttributeToText( NULL, attribute ) )
    return "a NULL Formatter returned an output";

  Output *output = RecordAttributeToText( formatter, attribute );
  if( !output )
    return "a full attribute could not be formatted";

  char *str = OutputToString( output );
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
  if( RecordAttributesToText( NULL, NULL ) )
    return "a NULL Formatter and attribute returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( RecordAttributesToText( formatter, NULL ) )
    return "a NULL Dictionary returned an Output";

  Dictionary *attributes = BuildDictionaryOfRecordAttributes();
  if( !attributes )
    return "could not build a test attribute Dictionary";

  if( RecordAttributesToText( NULL, attributes ) )
    return "a NULL Formatter returned an output";

  Output *output = RecordAttributesToText( formatter, attributes );
  if( !output )
    return "a Dictionary of attributes could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "Anonymous Attribute: anonymous value, Test Attribute 1: default value, Test Attribute 2: attribute value", str, "the attributes were not properly formatted" )

  return NULL;
}

const char *
TestValue
( void )
{
  if( ValueToText( NULL, NULL ) )
    return "a NULL Formatter and Value returned an Output";

  Formatter *formatter = FindFormatterByName( "text" );
  if( !formatter )
    return "the text Formatter could not be found";

  if( ValueToText( formatter, NULL ) )
    return "a NULL Value returned an Output";

  Value *value = BuildValue();
  if( !value )
    return "could not build a test Value";

  if( ValueToText( NULL, value ) )
    return "a NULL Formatter returned an output";

  Output *output = ValueToText( formatter, value );
  if( !output )
    return "a Value could not be formatted";

  char *str = OutputToString( output );
  if( !str )
    return "the Output could not be converted to a string";

  ASSERT_STRINGS_EQUAL( "6500", str, "the attributes were not properly formatted" )

  return NULL;
}
