#include <stdio.h>
#include <stdlib.h>

#include "private/handler.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_add_handler( void );
const char * test_find_handler_by_name( void );
const char * test_get_option( void );
const char * test_set_option( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;

  RUN_TEST( add_handler )
  RUN_TEST( find_handler_by_name )
  RUN_TEST( get_option )
  RUN_TEST( set_option )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_handler
( void )
{
  Handler *found, *handler, *result;

  handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )

  result = AddHandler( handler );
  if( result != handler )
    return "the new Handler could not be added";

  found = FindHandlerByName( handler->name );
  if( found != handler )
    return "the value was not added in such a way that it could be retrieved";

  return NULL;
}

const char *
test_find_handler_by_name
( void )
{
  Handler *handler;

  handler = BuildHandler();
  if( !handler )
    return "could not build test handler";

  AddHandler( handler );

  handler = FindHandlerByName( handler->name );
  FAIL_IF_NULL( handler, "the intended handler could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "test handler", handler->name, "the correct handler was not returned" )

  return NULL;
}

const char *
test_get_option
( void )
{
  const char *value;
  Handler *handler;

  handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )

  value = GetHandlerOption( NULL, NULL );
  FAIL_IF_NOT_NULL( value, "two NULL arguments returned a value" )

  value = GetHandlerOption( NULL, "whatever" );
  FAIL_IF_NOT_NULL( value, "a NULL handler returned a value" )

  value = GetHandlerOption( handler, NULL );
  FAIL_IF_NOT_NULL( value, "a NULL option name returned a value" )

  value = GetHandlerOption( handler, "non-existent option" );
  FAIL_IF_NOT_NULL( value, "a non-existent option returned a value" )

  value = GetHandlerOption( handler, "second" );
  FAIL_IF_NULL( value, "the returned value was NULL for an existent option" )
  ASSERT_STRINGS_EQUAL( "2nd", value, "the value returned for the option was not correct" )

  return NULL;
}

const char *
test_set_option
( void )
{
  const char *option = "test option";
  Handler *handler, *result;
  void *value = ( void * ) "target value";

  handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )

  result = SetHandlerOption( NULL, NULL, NULL );
  if( result )
    return "three NULL argument caused a problem";

  result = SetHandlerOption( NULL, NULL, value );
  if( result )
    return "only a Value caused a problem";

  result = SetHandlerOption( NULL, option, value );
  if( result )
    return "a NULL Handler caused a problem";

  result = SetHandlerOption( NULL, option, NULL );
  if( result )
    return "only an option caused a problem";

  result = SetHandlerOption( handler, NULL, value );
  if( result != handler )
    return "an empty option caused a problem";

  result = SetHandlerOption( handler, NULL, NULL );
  if( result != handler )
    return "only a Handler caused a problem";

  result = SetHandlerOption( handler, option, value );
  if( result != handler )
    return "could not set an option";

  return NULL;
}
