#include <stdio.h>
#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/filter/base.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_empty_record( void );
const char * test_empty_output( void );
const char * test_empty_value( void );
const char * test_level_record( void );
const char * test_level_output( void );
const char * test_level_value( void );
const char * test_invert_empty_record( void );
const char * test_invert_empty_output( void );
const char * test_invert_empty_value( void );
const char * test_invert_level_record( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;

  RUN_TEST( empty_record )
  RUN_TEST( empty_output )
  RUN_TEST( empty_value )
  RUN_TEST( level_record )
  RUN_TEST( level_output )
  RUN_TEST( level_value )
  RUN_TEST( invert_empty_record )
  RUN_TEST( invert_empty_output )
  RUN_TEST( invert_empty_value )
  RUN_TEST( invert_level_record )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_empty_record
( void )
{
  Filter *filter;
  Record *record = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = EmptyFilterAcceptRecord( filter, record );
  if( accepted )
    return "a null record was accepted by the default empty filter";

  record = BuildRecord();
  FAIL_IF_NULL( record, "the test record could not be built" )
  accepted = EmptyFilterAcceptRecord( filter, record );
  if( !accepted )
    return "a full record was not accepted by the default empty filter";

  record = BuildEmptyRecord();
  FAIL_IF_NULL( record, "the test empty record could not be built" )
  accepted = EmptyFilterAcceptRecord( filter, record );
  if( accepted )
    return "a non-null empty record was accepted by the default empty filter";

  return NULL;
}

const char *
test_empty_output
( void )
{
  Filter *filter;
  Output *output = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = EmptyFilterAcceptOutput( filter, output );
  if( accepted )
    return "a null output was accepted by the default empty filter";

  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  accepted = EmptyFilterAcceptOutput( filter, output );
  if( !accepted )
    return "a full output was not accepted by the default empty filter";

  output = BuildEmptyOutput();
  FAIL_IF_NULL( output, "the test empty output could not be built" )
  accepted = EmptyFilterAcceptOutput( filter, output );
  if( accepted )
    return "a non-null empty output was accepted by the default empty filter";

  return NULL;
}

const char *
test_level_record
( void )
{
  Filter *filter;
  Record *record = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = LevelFilterAcceptRecord( filter, record );
  if( accepted )
    return "a null record was accepted by the default level filter";

  record = BuildRecord();
  FAIL_IF_NULL( record, "the test record could not be built" )
  FAIL_IF_NULL( record->event, "the test record did not have an event" )
  FAIL_IF_NULL( record->event->level, "the test record did not have a level" )
  accepted = LevelFilterAcceptRecord( filter, record );
  if( !accepted )
    return "an record with a level was not accepted by the default level filter";

  return NULL;
}

const char *
test_level_output
( void )
{
  Filter *filter;
  Output *output = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = LevelFilterAcceptOutput( filter, output );
  if( !accepted )
    return "the level filter did not accept a NULL output";

  output = BuildTextOutput();
  FAIL_IF_NULL( output, "could not build the test output" )
  accepted = LevelFilterAcceptOutput( filter, output );
  if( !accepted )
    return "the level filter did not accept a normal output";

  return NULL;
}

const char *
test_level_value
( void )
{
  Filter *filter;
  unsigned short accepted;
  Value *value = NULL;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = LevelFilterAcceptValue( filter, value );
  if( !accepted )
    return "the level filter did not accept a NULL value";

  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "could not build the test value" )
  accepted = LevelFilterAcceptValue( filter, value );
  if( !accepted )
    return "the level filter did not accept a normal value";

  return NULL;
}

const char *
test_empty_value
( void )
{
  Filter *filter;
  unsigned short accepted;
  Value *value;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  accepted = EmptyFilterAcceptValue( filter, NULL );
  if( accepted )
    return "a null value was accepted by the default empty filter";

  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "the test value could not be built" )
  accepted = EmptyFilterAcceptValue( filter, value );
  if( !accepted )
    return "a full value was not accepted by the default empty filter";

  return NULL;
}

const char *
test_invert_empty_record
( void )
{
  Dictionary *result;
  Filter *filter;
  Record *record = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  filter->options = NewDictionary();
  FAIL_IF_NULL( filter->options, "the option dictionary could not be created" )
  result = SetDictionaryValue( filter->options, "invert", "non-null value" );
  if( result != filter->options )
    return "the invert option could not be set";

  accepted = EmptyFilterAcceptRecord( filter, record );
  if( !accepted )
    return "a null record was not accepted by an inverted empty filter";

  record = BuildRecord();
  FAIL_IF_NULL( record, "the test record could not be built" )
  accepted = EmptyFilterAcceptRecord( filter, record );
  if( accepted )
    return "a full record was accepted by an inverted empty filter";

  record = BuildEmptyRecord();
  FAIL_IF_NULL( record, "the test empty record could not be built" )
  accepted = EmptyFilterAcceptRecord( filter, record );
  if( !accepted )
    return "a non-null empty record was not accepted by an inverted empty filter";

  return NULL;
}

const char *
test_invert_empty_output
( void )
{
  Dictionary *result;
  Filter *filter;
  Output *output = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  filter->options = NewDictionary();
  FAIL_IF_NULL( filter->options, "the option dictionary could not be created" )
  result = SetDictionaryValue( filter->options, "invert", "non-null value" );
  if( result != filter->options )
    return "the invert option could not be set";

  accepted = EmptyFilterAcceptOutput( filter, output );
  if( !accepted )
    return "a null output was not accepted by an inverted empty filter";

  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  accepted = EmptyFilterAcceptOutput( filter, output );
  if( accepted )
    return "a full output was accepted by an inverted empty filter";

  output = BuildEmptyOutput();
  FAIL_IF_NULL( output, "the test empty output could not be built" )
  accepted = EmptyFilterAcceptOutput( filter, output );
  if( !accepted )
    return "a non-null empty output was not accepted by an inverted empty filter";

  return NULL;
}

const char *
test_invert_empty_value
( void )
{
  Dictionary *result;
  Filter *filter;
  unsigned short accepted;
  Value *value;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  filter->options = NewDictionary();
  FAIL_IF_NULL( filter->options, "the option dictionary could not be created" )
  result = SetDictionaryValue( filter->options, "invert", "non-null value" );
  if( result != filter->options )
    return "the invert option could not be set";

  accepted = EmptyFilterAcceptValue( filter, NULL );
  if( !accepted )
    return "a null value was not accepted by an inverted empty filter";

  value = BuildUnsignedIntValue();
  FAIL_IF_NULL( value, "the test value could not be built" )
  accepted = EmptyFilterAcceptValue( filter, value );
  if( accepted )
    return "a full value was accepted by an inverted empty filter";

  return NULL;
}

const char *
test_invert_level_record
( void )
{
  Dictionary *result;
  Filter *filter;
  Record *record = NULL;
  unsigned short accepted;

  filter = BuildFilter();
  if( !filter )
    return "could not build test filter";

  filter->options = NewDictionary();
  FAIL_IF_NULL( filter->options, "the option dictionary could not be created" )
  result = SetDictionaryValue( filter->options, "invert", "non-null value" );
  if( result != filter->options )
    return "the invert option could not be set";

  accepted = LevelFilterAcceptRecord( filter, record );
  if( !accepted )
    return "a null record was not accepted by the an inverted level filter";

  record = BuildRecord();
  FAIL_IF_NULL( record, "the test record could not be built" )
  FAIL_IF_NULL( record->event, "the test record did not have an event" )
  FAIL_IF_NULL( record->event->level, "the test record did not have a level" )
  accepted = LevelFilterAcceptRecord( filter, record );
  if( accepted )
    return "an record with a level was accepted by the an inverted level filter";

  return NULL;
}
