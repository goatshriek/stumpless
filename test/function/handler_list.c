#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/handler_list.h"
#include "private/static/handler_list.h"
#include "private/type.h"

#include "helper.h"

const char * test_appender( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_next( void );
const char * test_output_through( void );
const char * test_prepender( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( appender )
  RUN_TEST( begin )
  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( is_empty )
  RUN_TEST( next )
  RUN_TEST( output_through )
  RUN_TEST( prepender )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_appender
( void )
{
  Status * status;
  HandlerList * list = NewHandlerList();
  if( list == NULL )
    return "the list was not created";
  
  Handler * handler_1 = BuildHandler();
  handler_1->name = "first test handler";
  
  Handler * handler_2 = BuildHandler();
  handler_2->name = "second test handler";
  
  Handler * handler_3 = BuildHandler();
  handler_3->name = "third test handler";
  
  Handler * handler_4 = BuildHandler();
  handler_4->name = "fourth test handler";
  
  status = AppendToHandlerList( list, handler_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToHandlerList( list, handler_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToHandlerList( list, handler_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToHandlerList( list, handler_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Handler * handler = BeginHandlerList( list );
  FAIL_IF_NULL( handler, "the list did not have a first node" )
  if( handler != handler_1 )
    return "the first handler was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  HandlerList * list = BuildHandlerList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Handler * handler = BeginHandlerList( list );
  FAIL_IF_NULL( handler, "a handler was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  HandlerList * list = NULL;
  
  list = NewHandlerList();
  
  if( list == NULL )
    return "the list was not created";
  
  Handler * handler = BeginHandlerList( list );
  FAIL_IF_NOT_NULL( handler, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  HandlerList * list = BuildHandlerList();
  if( list == NULL )
    return "could not build the test list";
  
  HandlerList * copy;
  
  copy = CopyHandlerList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyHandlerList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Handler * original_handler = BeginHandlerList( list );
  Handler * copy_handler = BeginHandlerList( copy );
  while( original_handler != NULL ){
    if( original_handler != copy_handler )
      return "the copy was not an accurate copy of the original";
    original_handler = NextInHandlerList( list );
    copy_handler = NextInHandlerList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  HandlerList * list = NewHandlerList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyHandlerList( list );
  
  list = BuildHandlerList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyHandlerList( list );
  
  return NULL;
}

const char *
test_is_empty( void )
{
  HandlerList * list = NULL;
  if( !HandlerListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewHandlerList();
  if( !HandlerListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildHandlerList();
  if( list == NULL )
    return "could not build the test list";
  if( HandlerListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  HandlerList * list = BuildHandlerList();
  FAIL_IF_NULL( list, "could not build the test list" )
  AppendToHandlerList( list, malloc( sizeof( Handler ) ) );
  
  Handler * handler = BeginHandlerList( list );
  FAIL_IF_NULL( handler, "a handler was not returned from the start call" )
  
  handler = NextInHandlerList( list );
  FAIL_IF_NULL( handler, "a handler was not returned from the next call" )
  
  return NULL;
}

const char *
test_output_through
( void )
{
  Output * output = NULL;
  HandlerList * list = BuildHandlerList();
  FAIL_IF_NULL( list, "could not build the test list" )
  Status * status;
  
  status = OutputThroughHandlerList( list, output );
  FAIL_IF_NULL( status, "a null output did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a null output did not generate an empty argument error" )
  
  output = BuildTextOutput();
  FAIL_IF_NULL( output, "could not build the test output" )
  status = OutputThroughHandlerList( list, output );
  FAIL_IF_NOT_NULL( status, "a full output could not pass through the handler list" )
  
  return NULL;
}

const char *
test_prepender
( void )
{
  HandlerList * list = NewHandlerList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Handler * handler = BuildHandler();
  FAIL_IF_NULL( list, "could not build the test handler" );
  
  Status * status = PrependToHandlerList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToHandlerList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToHandlerList( NULL, handler );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToHandlerList( list, handler );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Handler * retrieved_handler = BeginHandlerList( list );
  FAIL_IF_NULL( retrieved_handler, "the list's nodes were invalid" )
  if( retrieved_handler != handler )
    return "the handler was not actually prepended to the list";
  
  list = BuildHandlerList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  handler = BuildHandler();
  FAIL_IF_NULL( list, "could not build a test handler" )
  status = PrependToHandlerList( list, handler );
  FAIL_IF_NOT_NULL( status, "the handler was not correctly prepended to a populated list" )
  retrieved_handler = BeginHandlerList( list );
  FAIL_IF_NULL( retrieved_handler, "a populated list had its members removed" )
  if( retrieved_handler != handler )
    return "the handler was not actually prepended to a full list";
  
  return NULL;
}
