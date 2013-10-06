#include <stdlib.h>
#include <stdio.h>

#include "private/status.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_status( void );
const char * test_find_status_by_name( void );
const char * test_raise_abnormal_status( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_status )
  RUN_TEST( find_status_by_name )
  RUN_TEST( raise_abnormal_status )
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_status
( void )
{
  Status * status = BuildErrorStatus();
  
  if( AddStatus( status ) != status )
    return "the status was not added to the list";
  
  return NULL;
}

const char *
test_find_status_by_name
( void )
{
  Status * status = BuildFailureStatus();
  FAIL_IF_NULL( status, "could not build the test status" )
  
  if( AddStatus( status ) != status )
    return "the status was not added to the list";
  
  if( FindStatusByName( status->name ) != status )
    return "the status returned was not the correct one";
  
  return NULL;
}

const char *
test_raise_abnormal_status
( void )
{
  Status * status = BuildWarningStatus();
  FAIL_IF_NULL( status, "could not build the test status" )
  
  if( AddStatus( status ) != status )
    return "the test status could not be added";
  
  if( RaiseAbnormalStatus( status->name ) != status )
    return "raising a status did not return the proper status";
  
  if( GetLastWarning() != status )
    return "the status was not properly registered before being raised";
  
  return NULL;
}

const char *
test_to_string
( void )
{
  Status * status = NULL;
  
  FAIL_IF_NOT_NULL( StatusToString( NULL ), "a NULL status did not return a NULL string" )
  
  status = BuildErrorStatus();
  FAIL_IF_NULL( status, "the test status could not be built" )
  
  
  return NULL;
}
