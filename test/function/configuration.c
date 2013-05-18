#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

#include "helper.h"

const char * test_add_new_profile( void );
const char * test_find_profile_by_name( void );
const char * test_initialization( void );
const char * test_profile_initialization( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_new_profile )
  RUN_TEST( find_profile_by_name )
  RUN_TEST( initialization )
  RUN_TEST( profile_initialization )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_new_profile( void )
{
  StumplessCustomProfile * profile = BuildCustomProfile();
  FAIL_IF_NULL( profile, "could not build the test profile" )
  
  StumplessProfileIndex index = StumplessAddCustomProfile( profile );
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  if( configuration->profiles[index] != profile )
    return "the profile was not actually added to the list";
  
  return NULL;
}

const char *
test_find_profile_by_name( void )
{
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  StumplessProfileIndex index = StumplessFindProfileByName( "Short" );
  if( index == STUMPLESS_INVALID_INDEX )
    return "an existing profile could not be found";
  
  index = StumplessFindProfileByName( "non-existent" );
  if( index != STUMPLESS_INVALID_INDEX )
    return "a non-existing profile was found";
  
  return NULL;
}

const char *
test_initialization( void )
{
  if( StumplessInitializeConfiguration() != STUMPLESS_SUCCESS )
    return "initialization method returned error code";

  StumplessConfiguration * configuration = StumplessGetConfiguration();
  
  if( configuration == NULL )
    return "configuration was not initialized after call";
  
  if( configuration->file == NULL )
    return "file configuration was not initialized";
  
  if( configuration->http == NULL )
    return "http configuration was not initialized";
  
  if( configuration->multithreading == NULL )
    return "multithreading configuration was not initialized";
  
  if( configuration->sorting == NULL )
    return "sorting configuration was not initialized";
  
  if( configuration->string == NULL )
    return "string configuration was not initialized";
  
  return NULL;
}

const char *
test_profile_initialization( void )
{
  if( StumplessInitializeProfiles() != STUMPLESS_SUCCESS )
    return "intializing the profiles was not successful";
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be returned" )
  
  FAIL_IF_NULL( configuration->profiles, "the profiles were not initialized" )
  
  return NULL;
}
