#include <stdlib.h>
#include <stdio.h>

#include "private/status.h"
#include "private/status_initializer.h"
#include "private/type.h"

#include "helper.h"

const char * test_initialize_by_name( void );
const char * test_initialize_constructor_failure( void );
const char * test_initialize_empty_argument( void );
const char * test_initialize_malformed_structure( void );
const char * test_initialize_memory_allocation_failure( void );
const char * test_initialize_string_write_failure( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( initialize_by_name )
  RUN_TEST( initialize_constructor_failure )
  RUN_TEST( initialize_empty_argument )
  RUN_TEST( initialize_malformed_structure )
  RUN_TEST( initialize_memory_allocation_failure )
  RUN_TEST( initialize_string_write_failure )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialize_by_name
( void )
{
  Status * status = InitializeStatusByName( "empty argument" );
  FAIL_IF_NULL( status, "the test status could not be found" )
  
  status = FindStatusByName( "empty argument" );
  FAIL_IF_NULL( status, "after being initialized, the status was not loaded" )
  
  return NULL;
}

const char *
test_initialize_constructor_failure
( void )
{
  Status * status = InitializeConstructorFailureStatus();
  FAIL_IF_NULL( status, "the status was not created" )
  
  ASSERT_STRINGS_EQUAL( "constructor failure", status->name, "the correct status was not returned from initialization" )
  
  return NULL;
}

const char *
test_initialize_empty_argument
( void )
{
  Status * status = InitializeEmptyArgumentStatus();
  FAIL_IF_NULL( status, "the status was not created" )
  
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the correct status was not returned from initialization" )
  
  return NULL;
}

const char *
test_initialize_malformed_structure
( void )
{
  Status * status = InitializeMalformedStructureStatus();
  FAIL_IF_NULL( status, "the status was not created" )
  
  ASSERT_STRINGS_EQUAL( "malformed structure", status->name, "the correct status was not returned from initialization" )
  
  return NULL;
}

const char *
test_initialize_memory_allocation_failure
( void )
{
  Status * status = InitializeMemoryAllocationFailureStatus();
  FAIL_IF_NULL( status, "the status was not created" )
  
  ASSERT_STRINGS_EQUAL( "memory allocation failure", status->name, "the correct status was not returned from initialization" )
  
  return NULL;
}

const char *
test_initialize_string_write_failure
( void )
{
  Status * status = InitializeStringWriteFailureStatus();
  FAIL_IF_NULL( status, "the status was not created" )
  
  ASSERT_STRINGS_EQUAL( "string write failure", status->name, "the correct status was not returned from initialization" )
  
  return NULL;
}
