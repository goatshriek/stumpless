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
  Filter *filter, *found;
  Exception *e;

  filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )

  e = AddFilter( filter );
  FAIL_IF_NOT_NULL( e, "the new filter could not be added" )

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
  Filter *filter;
  Exception *e;
  void *value = "target value";

  filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )

  e = SetFilterOption( NULL, NULL, NULL );
  FAIL_IF_NULL( e, "three NULL arguments did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( NULL, NULL, value );
  FAIL_IF_NULL( e, "only a value did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( NULL, option, value );
  FAIL_IF_NULL( e, "a NULL filter did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( NULL, option, NULL );
  FAIL_IF_NULL( e, "only an option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( filter, NULL, value );
  FAIL_IF_NULL( e, "an empty option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( filter, NULL, NULL );
  FAIL_IF_NULL( e, "only a filter did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetFilterOption( filter, option, value );
  FAIL_IF_NOT_NULL( e, "could not set an option" )

  return NULL;
}
