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
  Handler *found, *handler;
  Exception *e;

  handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )

  e = AddHandler( handler );
  FAIL_IF_NOT_NULL( e, "the new handler could not be added" )

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
  Handler *handler;
  Exception *e;
  void *value = ( void * ) "target value";

  handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )

  e = SetHandlerOption( NULL, NULL, NULL );
  FAIL_IF_NULL( e, "three NULL arguments did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( NULL, NULL, value );
  FAIL_IF_NULL( e, "only a value did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( NULL, option, value );
  FAIL_IF_NULL( e, "a NULL handler did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( NULL, option, NULL );
  FAIL_IF_NULL( e, "only an option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( handler, NULL, value );
  FAIL_IF_NULL( e, "an empty option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( handler, NULL, NULL );
  FAIL_IF_NULL( e, "only a handler did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "the error raised by empty argument was not correct" )

  e = SetHandlerOption( handler, option, value );
  FAIL_IF_NOT_NULL( e, "could not set an option" )

  return NULL;
}
