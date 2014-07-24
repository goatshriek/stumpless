#include <stdio.h>
#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/filter/base.h"
#include "private/type.h"

#include "helper.h"

const char * test_empty_entry( void );
const char * test_empty_output( void );
const char * test_empty_value( void );
const char * test_level_entry( void );
const char * test_level_output( void );
const char * test_level_value( void );
const char * test_invert_empty_entry( void );
const char * test_invert_empty_output( void );
const char * test_invert_empty_value( void );
const char * test_invert_level_entry( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( empty_entry )
  RUN_TEST( empty_output )
  RUN_TEST( empty_value )
  RUN_TEST( level_entry )
  RUN_TEST( level_output )
  RUN_TEST( level_value )
  RUN_TEST( invert_empty_entry )
  RUN_TEST( invert_empty_output )
  RUN_TEST( invert_empty_value )
  RUN_TEST( invert_level_entry )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_empty_entry
( void )
{
  Entry * entry = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( accepted )
    return "a null entry was accepted by the default empty filter";
  
  entry = BuildEntry();
  FAIL_IF_NULL( entry, "the test entry could not be built" )
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( !accepted )
    return "a full entry was not accepted by the default empty filter";
  
  entry = BuildEmptyEntry();
  FAIL_IF_NULL( entry, "the test empty entry could not be built" )
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( accepted )
    return "a non-null empty entry was accepted by the default empty filter";
  
  return NULL;
}

const char *
test_empty_output
( void )
{
  Output * output = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = EmptyFilterAcceptOutput( output, options );
  if( accepted )
    return "a null output was accepted by the default empty filter";
  
  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  accepted = EmptyFilterAcceptOutput( output, options );
  if( !accepted )
    return "a full output was not accepted by the default empty filter";
  
  output = BuildEmptyOutput();
  FAIL_IF_NULL( output, "the test empty output could not be built" )
  accepted = EmptyFilterAcceptOutput( output, options );
  if( accepted )
    return "a non-null empty output was accepted by the default empty filter";
  
  return NULL;
}

const char *
test_level_entry
( void )
{
  Entry * entry = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = LevelFilterAcceptEntry( entry, options );
  if( accepted )
    return "a null entry was accepted by the default level filter";
  
  entry = BuildEntry();
  FAIL_IF_NULL( entry, "the test entry could not be built" )
  FAIL_IF_NULL( entry->event, "the test entry did not have an event" )
  FAIL_IF_NULL( entry->event->level, "the test entry did not have a level" )
  accepted = LevelFilterAcceptEntry( entry, options );
  if( !accepted )
    return "an entry with a level was not accepted by the default level filter";
  
  return NULL;
}

const char *
test_level_output
( void )
{
  Output * output = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = LevelFilterAcceptOutput( output, options );
  if( !accepted )
    return "the level filter did not accept a NULL output";
  
  output = BuildTextOutput();
  FAIL_IF_NULL( output, "could not build the test output" )
  accepted = LevelFilterAcceptOutput( output, options );
  if( !accepted )
    return "the level filter did not accept a normal output";
  
  return NULL;
}

const char *
test_level_value
( void )
{
  Value * value = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = LevelFilterAcceptValue( value, options );
  if( !accepted )
    return "the level filter did not accept a NULL value";
  
  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "could not build the test value" )
  accepted = LevelFilterAcceptValue( value, options );
  if( !accepted )
    return "the level filter did not accept a normal value";
  
  return NULL;
}

const char *
test_empty_value
( void )
{
  Value * value = NULL;
  Dictionary * options = NULL;
  unsigned short accepted;
  
  accepted = EmptyFilterAcceptValue( value, options );
  if( accepted )
    return "a null value was accepted by the default empty filter";
  
  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "the test value could not be built" )
  accepted = EmptyFilterAcceptValue( value, options );
  if( !accepted )
    return "a full value was not accepted by the default empty filter";
  
  value = BuildEmptyValue();
  FAIL_IF_NULL( value, "the test empty value could not be built" )
  accepted = EmptyFilterAcceptValue( value, options );
  if( accepted )
    return "a non-null empty value was accepted by the default empty filter";
  
  return NULL;
}

const char *
test_invert_empty_entry
( void )
{
  Entry * entry = NULL;
  unsigned short accepted;

  Dictionary * options = NewDictionary();
  FAIL_IF_NULL( options, "the option dictionary could not be created" )
  Dictionary * result = SetDictionaryValue( options, "invert", "non-null value" );
  if( result != options )
    return "the invert option could not be set";
  
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( !accepted )
    return "a null entry was not accepted by an inverted empty filter";
  
  entry = BuildEntry();
  FAIL_IF_NULL( entry, "the test entry could not be built" )
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( accepted )
    return "a full entry was accepted by an inverted empty filter";
  
  entry = BuildEmptyEntry();
  FAIL_IF_NULL( entry, "the test empty entry could not be built" )
  accepted = EmptyFilterAcceptEntry( entry, options );
  if( !accepted )
    return "a non-null empty entry was not accepted by an inverted empty filter";
  
  return NULL;
}

const char *
test_invert_empty_output
( void )
{
  Output * output = NULL;
  unsigned short accepted;

  Dictionary * options = NewDictionary();
  FAIL_IF_NULL( options, "the option dictionary could not be created" )
  Dictionary * result = SetDictionaryValue( options, "invert", "non-null value" );
  if( result != options )
    return "the invert option could not be set";
  
  accepted = EmptyFilterAcceptOutput( output, options );
  if( !accepted )
    return "a null output was not accepted by an inverted empty filter";
  
  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  accepted = EmptyFilterAcceptOutput( output, options );
  if( accepted )
    return "a full output was accepted by an inverted empty filter";
  
  output = BuildEmptyOutput();
  FAIL_IF_NULL( output, "the test empty output could not be built" )
  accepted = EmptyFilterAcceptOutput( output, options );
  if( !accepted )
    return "a non-null empty output was not accepted by an inverted empty filter";
  
  return NULL;
}

const char *
test_invert_empty_value
( void )
{
  Value * value = NULL;
  unsigned short accepted;

  Dictionary * options = NewDictionary();
  FAIL_IF_NULL( options, "the option dictionary could not be created" )
  Dictionary * result = SetDictionaryValue( options, "invert", "non-null value" );
  if( result != options )
    return "the invert option could not be set";
  
  accepted = EmptyFilterAcceptValue( value, options );
  if( !accepted )
    return "a null value was not accepted by an inverted empty filter";
  
  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "the test value could not be built" )
  accepted = EmptyFilterAcceptValue( value, options );
  if( accepted )
    return "a full value was accepted by an inverted empty filter";
  
  value = BuildEmptyValue();
  FAIL_IF_NULL( value, "the test empty value could not be built" )
  accepted = EmptyFilterAcceptValue( value, options );
  if( !accepted )
    return "a non-null empty value was not accepted by an inverted empty filter";
  
  return NULL;
}

const char *
test_invert_level_entry
( void )
{
  Entry * entry = NULL;
  unsigned short accepted;

  Dictionary * options = NewDictionary();
  FAIL_IF_NULL( options, "the option dictionary could not be created" )
  Dictionary * result = SetDictionaryValue( options, "invert", "non-null value" );
  if( result != options )
    return "the invert option could not be set";
  
  accepted = LevelFilterAcceptEntry( entry, options );
  if( !accepted )
    return "a null entry was not accepted by the an inverted level filter";
  
  entry = BuildEntry();
  FAIL_IF_NULL( entry, "the test entry could not be built" )
  FAIL_IF_NULL( entry->event, "the test entry did not have an event" )
  FAIL_IF_NULL( entry->event->level, "the test entry did not have a level" )
  accepted = LevelFilterAcceptEntry( entry, options );
  if( accepted )
    return "an entry with a level was accepted by the an inverted level filter";
  
  return NULL;
}
