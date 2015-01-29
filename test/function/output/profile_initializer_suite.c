#include <stdlib.h>
#include <stdio.h>

#include "private/output/profile.h"
#include "private/output/profile_initializer.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_initialize_by_name( void );
const char * test_initialize_text( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( initialize_by_name )
  RUN_TEST( initialize_text )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialize_by_name
( void )
{
  OutputProfile *profile, *result;

  result = InitializeOutputProfileByName( "text" );
  if( !result )
    return "the test profile could not be initialized";

  profile = FindOutputProfileByName( "text" );
  FAIL_IF_NULL( profile, "after being initialized, the profile was not loaded" )
  ASSERT_STRINGS_EQUAL( "text", profile->name, "the incorrect profile was returned" )

  return NULL;
}

const char *
test_initialize_text
( void )
{
  OutputProfile *profile;

  profile = InitializeTextOutputProfile();
  FAIL_IF_NULL( profile, "the profile was not created" )

  ASSERT_STRINGS_EQUAL( "text", profile->name, "the correct profile was not returned from initialization" )

  return NULL;
}
