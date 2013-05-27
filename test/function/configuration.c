#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

#include "helper.h"

const char * test_add_new_output_profile( void );
const char * test_add_new_value_profile( void );
const char * test_find_output_profile_by_name( void );
const char * test_find_value_profile_by_name( void );
const char * test_initialization( void );
const char * test_output_profile_initialization( void );
const char * test_value_profile_initialization( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_new_output_profile )
  RUN_TEST( add_new_value_profile )
  RUN_TEST( find_output_profile_by_name )
  RUN_TEST( find_value_profile_by_name )
  RUN_TEST( initialization )
  RUN_TEST( output_profile_initialization )
  RUN_TEST( value_profile_initialization )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_new_output_profile( void )
{
  StumplessOutputProfile * profile = BuildOutputProfile();
  FAIL_IF_NULL( profile, "could not build the test profile" )
  
  StumplessStatusCode status = StumplessAddOutputProfile( profile );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  if( StumplessFindOutputProfileByName( profile->name ) != profile )
    return "the profile was not actually added to the list";
  
  return NULL;
}

const char *
test_add_new_value_profile( void )
{
  StumplessValueProfile * profile = BuildValueProfile();
  FAIL_IF_NULL( profile, "could not build the test profile" )
  
  StumplessStatusCode status = StumplessAddValueProfile( profile );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  if( StumplessFindValueProfileByName( profile->name ) != profile )
    return "the profile was not actually added to the list";
  
  return NULL;
}

const char *
test_find_output_profile_by_name( void )
{
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  StumplessOutputProfile * profile;
  profile = StumplessFindOutputProfileByName( "Stream" );
  FAIL_IF_NULL( profile, "an existing profile could not be found" )
  
  profile = StumplessFindOutputProfileByName( "non-existent" );
  FAIL_IF_NOT_NULL( profile, "a non-existing profile was found" )
  
  return NULL;
}

const char *
test_find_value_profile_by_name( void )
{
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  StumplessValueProfile * profile = StumplessFindValueProfileByName( "Short" );
  FAIL_IF_NULL( profile, "an existing profile could not be found" )
  
  profile = StumplessFindValueProfileByName( "non-existent" );
  FAIL_IF_NOT_NULL( profile, "a non-existing profile was found" )
  
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
test_output_profile_initialization( void )
{
  if( StumplessInitializeOutputProfiles() != STUMPLESS_SUCCESS )
    return "initializing the profiles was not successful";
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be returned" )
  
  FAIL_IF_NULL( configuration->output_profiles,
                "the profiles were not initialized" )
  
  return NULL;
}

const char *
test_value_profile_initialization( void )
{
  if( StumplessInitializeValueProfiles() != STUMPLESS_SUCCESS )
    return "intializing the profiles was not successful";
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be returned" )
  
  FAIL_IF_NULL( configuration->value_profiles,
                "the profiles were not initialized" )
  
  return NULL;
}
