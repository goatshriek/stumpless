#include <stdio.h>
#include <stdlib.h>

#include "private/container/list/filter.h"
#include "private/container/list/handler.h"
#include "private/container/list/iterator/filter.h"
#include "private/container/list/iterator/handler.h"
#include "private/formatter.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_add_formatter( void );
const char * test_destructor( void );
const char * test_find_formatter_by_name( void );
const char * test_get_option( void );
const char * test_set_option( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result = NULL;

  RUN_TEST( add_formatter )
  RUN_TEST( destructor )
  RUN_TEST( find_formatter_by_name )
  RUN_TEST( get_option )
  RUN_TEST( set_option )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_formatter
( void )
{
  Formatter *formatter, *found, *result;

  formatter = BuildFormatter();
  FAIL_IF_NULL( formatter, "the test formatter could not be built" )

  result = AddFormatter( formatter );
  if( result != formatter )
    return "the new formatter could not be added";

  found = FindFormatterByName( formatter->name );
  if( found != formatter )
    return "the value was not added in such a way that it could be retrieved";

  return NULL;
}

const char *
test_destructor
( void )
{
  Filter *filter;
  FilterListIterator *filters;
  Formatter *formatter;

  DestroyFormatter( NULL );

  formatter = BuildFormatter();
  if( !formatter )
    return NULL;

  filters = BeginFilterList( formatter->filters );
  filter = NextInFilterListIterator( filters );

  if( !filter || !filter->name )
    return "the formatter did not have a populated filter list";

  DestroyFormatter( formatter );

  if( !filter->name )
    return "the filters were destroyed when the formatter was destroyed";

  return NULL;
}

const char *
test_find_formatter_by_name
( void )
{
  Formatter *formatter;

  formatter = FindFormatterByName( "text" );
  FAIL_IF_NULL( formatter, "the intended formatter could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "text", formatter->name, "the correct formatter was not returned" )

  return NULL;
}

const char *
test_get_option
( void )
{
  const char *value;
  Formatter *formatter;

  formatter = BuildFormatter();
  FAIL_IF_NULL( formatter, "the test formatter could not be built" )

  value = GetFormatterOption( NULL, NULL );
  FAIL_IF_NOT_NULL( value, "two NULL arguments returned a value" )

  value = GetFormatterOption( NULL, "whatever" );
  FAIL_IF_NOT_NULL( value, "a NULL formatter returned a value" )

  value = GetFormatterOption( formatter, NULL );
  FAIL_IF_NOT_NULL( value, "a NULL option name returned a value" )

  value = GetFormatterOption( formatter, "non-existent option" );
  FAIL_IF_NOT_NULL( value, "a non-existent option returned a value" )

  value = GetFormatterOption( formatter, "first" );
  FAIL_IF_NULL( value, "the returned value was NULL for an existent option" )
  ASSERT_STRINGS_EQUAL( "1st", value, "the value returned for the option was not correct" )

  return NULL;
}

const char *
test_set_option
( void )
{
  const char *option = "test option";
  Formatter *formatter, *result;
  void *value = "target value";

  formatter = BuildFormatter();
  FAIL_IF_NULL( formatter, "the test formatter could not be built" )

  result = SetFormatterOption( NULL, NULL, NULL );
  if( result )
    return "three NULL arguments caused a problem";

  result = SetFormatterOption( NULL, NULL, value );
  if( result )
    return "only a Value caused a problem";

  result = SetFormatterOption( NULL, option, value );
  if( result )
    return "a NULL Formatter caused a problem";

  result = SetFormatterOption( NULL, option, NULL );
  if( result )
    return "only an option caused a problem";

  result = SetFormatterOption( formatter, NULL, value );
  if( result != formatter )
    return "an empty option caused a problem";

  result = SetFormatterOption( formatter, NULL, NULL );
  if( result != formatter )
    return "only a Formatter caused a problem";

  result = SetFormatterOption( formatter, option, value );
  if( result != formatter )
    return "could not set an option";

  return NULL;
}
