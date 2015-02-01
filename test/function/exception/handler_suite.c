#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception/handler.h>

#include "private/exception/thrower.h"
#include "private/type.h"
#include "test/function/exception/handler_suite.h"
#include "test/helper.h"
#include "test/helper/fixture.h"
#include "test/helper/log.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( GetMemoryAllocationExceptionHandler )
  TEST( SetMemoryAllocationExceptionHandler )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestGetMemoryAllocationExceptionHandler
( void )
{
  SetMemoryAllocationExceptionHandler( TestExceptionHandlerFunction );
  if( GetMemoryAllocationExceptionHandler() != TestExceptionHandlerFunction )
    return "the handler function was not returned after being set";

  SetMemoryAllocationExceptionHandler( NULL );
  if( GetMemoryAllocationExceptionHandler() )
    return "a handler function was returned after being set to NULL";

  return NULL;
}

const char *
TestSetMemoryAllocationExceptionHandler
( void )
{
  const Exception *e;

  InitializeTestLog();

  SetMemoryAllocationExceptionHandler( BadExceptionHandlerFunction );
  ThrowMemoryAllocationException();

  e = TestLogGetLastException();
  if( !e )
    return "the handler function was not called";
  ASSERT_STRINGS_EQUAL( "memory allocation failure", e->name, "the correct Exception was not thrown" )

  SetMemoryAllocationExceptionHandler( NULL );
  ThrowMemoryAllocationException();

  if( e != TestLogGetLastException() )
    return "the handler function was still called after resetting it to NULL";

  return NULL;
}
