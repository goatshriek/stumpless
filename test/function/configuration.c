#include <stdlib.h>
#include <stdio.h>

#include "private/configuration.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_new_logging_profile( void );
const char * test_add_new_output_profile( void );
const char * test_find_logging_profile_by_name( void );
const char * test_find_output_profile_by_name( void );
const char * test_initialization( void );
const char * test_logging_profile_initialization( void );
const char * test_output_profile_initialization( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_new_logging_profile )
  RUN_TEST( add_new_output_profile )
  RUN_TEST( find_logging_profile_by_name )
  RUN_TEST( find_output_profile_by_name )
  RUN_TEST( initialization )
  RUN_TEST( logging_profile_initialization )
  RUN_TEST( output_profile_initialization )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_new_logging_profile( void )
{
  LoggingProfile * profile = BuildLoggingProfile();
  FAIL_IF_NULL( profile, "could not build the test profile" )
  
  StatusCode status = AddLoggingProfile( profile );
  if( status != STUMPLESS_SUCCESS )
    return "the profile was not successfully added";
  
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  if( FindLoggingProfileByName( profile->name ) != profile )
    return "the profile was not actually added to the list";
  
  return NULL;
}

const char *
test_add_new_output_profile( void )
{
  OutputProfile * profile = BuildOutputProfile();
  FAIL_IF_NULL( profile, "could not build the test profile" )
  
  StatusCode status = AddOutputProfile( profile );
  if( status != STUMPLESS_SUCCESS )
    return "the profile was not successfully added";
  
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  if( FindOutputProfileByName( profile->name ) != profile )
    return "the profile was not actually added to the list";
  
  return NULL;
}

const char *
test_find_logging_profile_by_name( void )
{
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  LoggingProfile * profile;
  
  profile = FindLoggingProfileByName( "non-existent" );
  FAIL_IF_NOT_NULL( profile, "a non-existing profile was found" )
  
  return NULL;
}

const char *
test_find_output_profile_by_name( void )
{
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be retrieved" )
  
  OutputProfile * profile;
  profile = FindOutputProfileByName( "text" );
  FAIL_IF_NULL( profile, "an existing profile could not be found" )
  
  profile = FindOutputProfileByName( "non-existent" );
  FAIL_IF_NOT_NULL( profile, "a non-existing profile was found" )
  
  return NULL;
}

const char *
test_initialization( void )
{
  if( InitializeConfiguration() != STUMPLESS_SUCCESS )
    return "initialization method returned error code";

  Configuration * configuration = GetConfiguration();
  
  if( configuration == NULL )
    return "configuration was not initialized after call";
  
  if( configuration->file == NULL )
    return "file configuration was not initialized";
  
  if( configuration->http == NULL )
    return "http configuration was not initialized";
  
  if( configuration->sorting == NULL )
    return "sorting configuration was not initialized";
  
  if( configuration->string == NULL )
    return "string configuration was not initialized";
  
  if( configuration->threading == NULL )
    return "multithreading configuration was not initialized";
  
  return NULL;
}

const char *
test_logging_profile_initialization( void )
{
  if( InitializeLoggingProfiles() != STUMPLESS_SUCCESS )
    return "initializing the profiles was not successful";
  
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be returned" )
  
  FAIL_IF_NULL( configuration->logging_profiles,
                "the profiles were not initialized" )
  
  return NULL;
}
const char *
test_output_profile_initialization( void )
{
  if( InitializeOutputProfiles() != STUMPLESS_SUCCESS )
    return "initializing the profiles was not successful";
  
  Configuration * configuration = GetConfiguration();
  FAIL_IF_NULL( configuration, "the configuration could not be returned" )
  
  FAIL_IF_NULL( configuration->output_profiles,
                "the profiles were not initialized" )
  
  return NULL;
}
