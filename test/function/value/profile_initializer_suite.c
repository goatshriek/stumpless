#include <stdlib.h>
#include <stdio.h>

#include <stumpless/value/profile.h>

#include "private/type.h"
#include "private/value/profile_initializer.h"
#include "test/helper.h"

const char * test_initialize_boolean( void );
const char * test_initialize_boolean_array( void );
const char * test_initialize_by_name( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( initialize_boolean )
  RUN_TEST( initialize_boolean_array )
  RUN_TEST( initialize_by_name )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialize_boolean
( void )
{
  ValueProfile * profile = InitializeBooleanValueProfile();
  FAIL_IF_NULL( profile, "the profile was not created" )

  ASSERT_STRINGS_EQUAL( "boolean", profile->name, "the correct profile was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_boolean_array
( void )
{
  ValueProfile * profile = InitializeBooleanArrayValueProfile();
  FAIL_IF_NULL( profile, "the profile was not created" )

  ASSERT_STRINGS_EQUAL( "boolean array", profile->name, "the correct profile was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_by_name
( void )
{
  ValueProfile *profile, *result;

  result = InitializeValueProfileByName( "boolean" );
  if( !result )
    return "the test profile could not be initialized";

  profile = FindValueProfileByName( "boolean" );
  FAIL_IF_NULL( profile, "after being initialized, the profile was not loaded" )
  ASSERT_STRINGS_EQUAL( "boolean", profile->name, "the incorrect profile was returned" )

  return NULL;
}
