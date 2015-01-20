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

  TEST( Add )
  TEST( Destroy )
  TEST( FindByName )
  TEST( GetLastFailure )
  TEST( GetLastInformational )
  TEST( GetLastWarning )
  TEST( Raise )
  TEST( ToString )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAdd
( void )
{
  Exception *e;

  if( AddException( NULL ) )
    return "a NULL Exception did not return NULL";

  e = BuildInformationalException();
  if( !e )
    return "could not build a test Exception";
  e->name = "add Exception test";

  if( FindExceptionByName( e->name ) )
    return "the test Exception already existed";

  if( AddException( e ) != e )
    return "the call to the function failed";

  if( FindExceptionByName( e->name ) != e )
    return "the Exception was not actually added";

  DestroyException( e );

  return NULL;
}

const char *
TestDestroy
( void )
{
  const char *name;
  Exception *e;

  DestroyException( NULL );

  e = BuildFailureException();
  if( !e )
    return "could not build a test failure Exception";

  DestroyException( e );

  e = BuildWarningException();
  if( !e )
    return "could not build a test warning Exception";
  if( !AddException( e ) )
    return "could not add the new Exception";
  name = e->name;
  if( FindExceptionByName( name ) != e )
    return "the Exception was not actually added";

  DestroyException( e );

  if( FindExceptionByName( name ) )
    return "the Exception was not removed from the list";

  return NULL;
}

const char *
TestFindByName
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

  DestroyException( e );

  return NULL;
}

const char *
TestGetLastFailure
( void )
{
  Exception *e;

  e = BuildFailureException();
  if( !e )
    return "could not build the a test failure Exception";

  if( AddException( e ) != e )
    return "the test failure Exception could not be added";

  if( RaiseException( e->name ) != e )
    return "the correct failure Exception was not returned";

  if( GetLastFailureException() != e )
    return "the failure Exception was not properly registered when raised";

  DestroyException( e );

  return NULL;
}

const char *
TestGetLastInformational
( void )
{
  Exception *e;

  e = BuildInformationalException();
  if( !e )
    return "could not build the a test informational Exception";

  if( AddException( e ) != e )
    return "the test informational Exception could not be added";

  if( RaiseException( e->name ) != e )
    return "the correct informational Exception was not returned";

  if( GetLastInformationalException() != e )
    return "the informational Exception was not properly registered when raised";

  DestroyException( e );

  return NULL;
}

const char *
TestGetLastWarning
( void )
{
  Exception *e;

  e = BuildWarningException();
  if( !e )
    return "could not build the a test warning Exception";

  if( AddException( e ) != e )
    return "the test warning exception could not be added";

  if( RaiseException( e->name ) != e )
    return "the correct warning Exception was not returned";

  if( GetLastFailureException() != e )
    return "the warning Exception was not properly registered when raised";

  DestroyException( e );

  return NULL;
}

const char *
TestRaise
( void )
{
  Exception *e;

  if( RaiseException( NULL ) )
    return "a NULL argument raised an Exception";

  if( RaiseException( "this name doesn't exist" ) )
    return "a non-existent Exception name returned an Exception";

  e = BuildFailureException();
  if( !e )
    return "could not build a test Exception";

  if( AddException( e ) != e )
    return "could not add a new Exception";

  if( RaiseException( e->name ) != e )
    return "the correct Exception was not returned";

  DestroyException( e );

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

  e = BuildInformationalException();
  if( !e )
    return "the test exception could not be built";

  str = ExceptionToString( e );
  if( !str )
    return "a valid Exception returned a NULL string";

  if( !strstr( str, e->name ) )
    return "the string did not contain the Exception's name";

  DestroyException( e );

  return NULL;
}
