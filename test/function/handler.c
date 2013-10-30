#include <stdio.h>
#include <stdlib.h>

#include "private/handler.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_handler( void );
const char * test_find_handler_by_name( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( add_handler )
  RUN_TEST( find_handler_by_name )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_handler
( void )
{
  Handler * handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )
  
  Status * status = AddHandler( handler );
  FAIL_IF_NOT_NULL( status, "the new handler could not be added" )
  
  Handler * found = FindHandlerByName( handler->name );
  if( found != handler )
    return "the value was not added in such a way that it could be retrieved";
  
  return NULL;
}

const char *
test_find_handler_by_name
( void )
{
  AddHandler( BuildHandler() );
  
  Handler * handler = FindHandlerByName( "test handler" );
  FAIL_IF_NULL( handler, "the intended handler could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "test handler", handler->name, "the correct handler was not returned" )
  
  return NULL;
}
