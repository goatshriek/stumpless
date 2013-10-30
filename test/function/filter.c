#include <stdio.h>
#include <stdlib.h>

#include "private/filter.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_filter( void );
const char * test_find_filter_by_name( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( add_filter )
  RUN_TEST( find_filter_by_name )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_filter
( void )
{
  Filter * filter = BuildFilter();
  FAIL_IF_NULL( filter, "the test filter could not be built" )
  
  Status * status = AddFilter( filter );
  FAIL_IF_NOT_NULL( status, "the new filter could not be added" )
  
  Filter * found = FindFilterByName( filter->name );
  if( found != filter )
    return "the value was not added in such a way that it could be retrieved";
  
  return NULL;
}

const char *
test_find_filter_by_name
( void )
{
  Filter * filter = FindFilterByName( "empty" );
  FAIL_IF_NULL( filter, "the intended filter could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "empty", filter->name, "the correct filter was not returned" )
  
  return NULL;
}
