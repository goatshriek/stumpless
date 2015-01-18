#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception.h>

#include "private/type.h"
#include "test/function/exception_suite.h"
#include "test/helper.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( AddException )
  TEST( FindExceptionByName )
  TEST( Raise )
  TEST( ToString )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAddException
( void )
{
  Exception *e;

  e = BuildInformationalException();
  if( !e )
    return "could not build a test Exception";

  if( AddException( e ) != e )
    return "the e was not added to the list";

  return NULL;
}

const char *
TestFindExceptionByName
( void )
{
  Exception *e;

  e = BuildFailureException();
  if( !e )
    return "could not build the test e";

  if( AddException( e ) != e )
    return "the e was not added to the list";

  if( FindExceptionByName( e->name ) != e )
    return "the e returned was not the correct one";

  return NULL;
}

const char *
TestRaise
( void )
{
  Exception *e;

  e = BuildWarningException();
  FAIL_IF_NULL( e, "could not build the test e" )

  if( AddException( e ) != e )
    return "the test exception could not be added";

  if( RaiseException( e->name ) != e )
    return "raising an exception did not return the proper e";

  if( GetLastWarningException() != e )
    return "the exception was not properly registered before being raised";

  return NULL;
}

const char *
TestToString
( void )
{
  Exception *e;

  if( ExceptionToString( NULL ) )
    return "a NULL exception did not return a NULL string";

  e = BuildInformationalException();
  if( !e )
    return "the test exception could not be built";

  return NULL;
}
