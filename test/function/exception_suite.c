#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception.h>

#include "test/function/exception_suite.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Destroy )
  TEST( ToString )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestDestroy
( void )
{
  Exception *e;

  DestroyException( NULL );

  e = BuildException();
  if( !e )
    return "could not build a test failure Exception";

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

  e = BuildException();
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
