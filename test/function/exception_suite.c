#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception.h>
#include <stumpless/exception/handler.h>

#include "private/exception/thrower.h"
#include "test/function/exception_suite.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Catch )
  TEST( ToString )
  TEST( GetUncaught )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestCatch
( void )
{
  Exception *e;

  CatchException( NULL );

  e = BuildException();
  if( !e )
    return "could not build test Exception";

  CatchException( e );

  return NULL;
}

const char *
TestToString
( void )
{
  char *str;
  Exception *e;

  if( ExceptionToString( NULL ) )
    return "a NULL exception did not return a NULL string";

  e = BuildException();
  if( !e )
    return "the test exception could not be built";

  str = ExceptionToString( e );
  if( !str )
    return "a valid Exception returned a NULL string";

  if( !strstr( str, e->name ) )
    return "the string did not contain the Exception's name";

  return NULL;
}

const char *
TestGetUncaught
( void )
{
  Exception *e1, *e2, *e3;

  if( GetUncaughtException() )
    return "an Exception was returned when none had been thrown";

  SetMemoryAllocationExceptionHandler( BadExceptionHandlerFunction );

  e1 = ThrowMemoryAllocationException();
  if( GetUncaughtException() != e1 )
    return "the first Exception thrown was not returned";

  e2 = ThrowMemoryAllocationException();
  if( GetUncaughtException() != e1 )
    return "the first Exception thrown was not returned after throwing a second Exception";

  CatchException( e1 );

  if( GetUncaughtException() != e2 )
    return "the second Exception was not returned after the first was caught";

  CatchException( e2 );

  if( GetUncaughtException() )
    return "an Exception was returned after all were caught";

  SetMemoryAllocationExceptionHandler( CatchException );

  e3 = ThrowMemoryAllocationException();

  if( GetUncaughtException() == e3 )
    return "an Exception caught by its handler was still returned";

  return NULL;
}
