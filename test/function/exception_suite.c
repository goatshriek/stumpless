#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception.h>

#include "private/type.h"
#include "test/helper.h"

const char * test_add_e( void );
const char * test_find_e_by_name( void );
const char * test_raise_abnormal_e( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( add_e )
  RUN_TEST( find_e_by_name )
  RUN_TEST( raise_abnormal_e )
  RUN_TEST( to_string )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_e
( void )
{
  Exception *e;

  e = BuildInformationalException();

  if( AddException( e ) != e )
    return "the e was not added to the list";

  return NULL;
}

const char *
test_find_e_by_name
( void )
{
  Exception *e;

  e = BuildFailureException();
  FAIL_IF_NULL( e, "could not build the test e" )

  if( AddException( e ) != e )
    return "the e was not added to the list";

  if( FindExceptionByName( e->name ) != e )
    return "the e returned was not the correct one";

  return NULL;
}

const char *
test_raise_abnormal_e
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
test_to_string
( void )
{
  Exception *e;

  FAIL_IF_NOT_NULL( ExceptionToString( NULL ), "a NULL exception did not return a NULL string" )

  e = BuildInformationalException();
  FAIL_IF_NULL( e, "the test exception could not be built" )

  return NULL;
}
