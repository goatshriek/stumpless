#include <stdio.h>
#include <stdlib.h>

#include "private/filter.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_add_filter( void );
const char * test_find_filter_by_name( void );
const char * test_get_option( void );
const char * test_set_option( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result = NULL;

  RUN_TEST( add_filter )
  RUN_TEST( find_filter_by_name )
  RUN_TEST( get_option )
  RUN_TEST( set_option )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_filter
( void )
{
  Filter *filter, *found, *result;

  filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )

  result = AddFilter( filter );
  if( result != filter )
    return "the new Filter could not be added";

  found = FindFilterByName( filter->name );
  if( found != filter )
    return "the value was not added in such a way that it could be retrieved";

  return NULL;
}

const char *
test_find_filter_by_name
( void )
{
  Filter *filter;

  filter = FindFilterByName( "empty" );
  FAIL_IF_NULL( filter, "the intended filter could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "empty", filter->name, "the correct filter was not returned" )

  return NULL;
}

const char *
test_get_option
( void )
{
  const char *value;
  Filter *filter;

  filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )

  value = GetFilterOption( NULL, NULL );
  FAIL_IF_NOT_NULL( value, "two NULL arguments returned a value" )

  value = GetFilterOption( NULL, "whatever" );
  FAIL_IF_NOT_NULL( value, "a NULL filter returned a value" )

  value = GetFilterOption( filter, NULL );
  FAIL_IF_NOT_NULL( value, "a NULL option name returned a value" )

  value = GetFilterOption( filter, "non-existent option" );
  FAIL_IF_NOT_NULL( value, "a non-existent option returned a value" )

  value = GetFilterOption( filter, "first" );
  FAIL_IF_NULL( value, "the returned value was NULL for an existent option" )
  ASSERT_STRINGS_EQUAL( "1st", value, "the value returned for the option was not correct" )

  return NULL;
}

const char *
test_set_option
( void )
{
  const char *option = "test option";
  Filter *filter, *result;
  void *value = "target value";

  filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )

  result = SetFilterOption( NULL, NULL, NULL );
  if( result )
    return "three NULL arguments caused a problem";

  result = SetFilterOption( NULL, NULL, value );
  if( result )
    return "only a Value caused a problem";

  result = SetFilterOption( NULL, option, value );
  if( result )
    return "a NULL Filter caused a problem";

  result = SetFilterOption( NULL, option, NULL );
  if( result )
    return "only an option caused a problem";

  result = SetFilterOption( filter, NULL, value );
  if( result != filter )
    return "an empty option caused a problem";

  result = SetFilterOption( filter, NULL, NULL );
  if( result != filter )
    return "only a Filter caused a problem";

  result = SetFilterOption( filter, option, value );
  if( result != filter )
    return "could not set an option";

  return NULL;
}
