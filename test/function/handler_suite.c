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

const char *
test_get_option
( void )
{
  Handler * handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )
  
  const char * value = GetHandlerOption( NULL, NULL );
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
  Handler * handler = BuildHandler();
  FAIL_IF_NULL( handler, "the test handler could not be built" )
  
  const char * option = "test option";
  void * value = ( void * ) "target value";
  
  Status * status = SetHandlerOption( NULL, NULL, NULL );
  FAIL_IF_NULL( status, "three NULL arguments did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( NULL, NULL, value );
  FAIL_IF_NULL( status, "only a value did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( NULL, option, value );
  FAIL_IF_NULL( status, "a NULL handler did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( NULL, option, NULL );
  FAIL_IF_NULL( status, "only an option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( handler, NULL, value );
  FAIL_IF_NULL( status, "an empty option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( handler, NULL, NULL );
  FAIL_IF_NULL( status, "only a handler did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetHandlerOption( handler, option, value );
  FAIL_IF_NOT_NULL( status, "could not set an option" )
  
  return NULL;
}
