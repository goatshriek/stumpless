#include <stdlib.h>

#include <configuration.h>
#include <status_checker.h>
#include <type.h>

#define ADD_PROFILE( profile_name, prefix )                                    \
profile = malloc( sizeof( StumplessCustomProfile ) );                          \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->name = profile_name;                                                  \
profile->binary_formatter = NULL;                                              \
profile->csv_formatter = NULL;                                                 \
profile->json_formatter = NULL;                                                \
profile->text_formatter = NULL;                                                \
profile->xml_formatter = NULL;                                                 \
StumplessAddCustomProfile( profile );

static StumplessConfiguration * configuration = NULL;
static unsigned profile_array_capacity = 0;

StumplessProfileIndex
StumplessAddCustomProfile( StumplessCustomProfile * profile )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  StumplessProfileIndex index = configuration->profile_count;
  
  configuration->profiles[index] = profile;
  configuration->profile_count++;
  
  return index;
}

StumplessCustomProfile *
StumplessFindProfileByIndex( StumplessProfileIndex index )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  if( index >= configuration->profile_count )
    return NULL;
  else
    return configuration->profiles[index];
}

StumplessCustomProfile *
StumplessFindProfileByName( const char * name )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  unsigned i;
  for( i = 0; i < configuration->profile_count; i++ )
    if( strcmp( configuration->profiles[i]->name, name ) == 0 )
      return configuration->profiles[i];
  
  return NULL;
}

StumplessConfiguration *
StumplessGetConfiguration( void )
{
  if( configuration == NULL )
    NULL_ON_FAILURE( StumplessInitializeConfiguration() )
  
  return configuration;
}

StumplessStatusCode
StumplessInitializeConfiguration( void )
{
  configuration = malloc( sizeof( StumplessConfiguration ) );
  if( configuration == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  size_t required_size = sizeof( StumplessFileConfiguration );
  configuration->file = malloc( required_size );
  if( configuration->file == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  required_size = sizeof( StumplessHTTPConfiguration );
  configuration->http = malloc( required_size );
  if( configuration->http == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessMultithreadingConfiguration );
  configuration->multithreading = malloc( required_size );
  if( configuration->multithreading == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessSortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( configuration->sorting == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessStringConfiguration );
  configuration->string = malloc( required_size );
  if( configuration->string == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  configuration->string->buffer_size = 100;

  return StumplessInitializeProfiles();
}

StumplessStatusCode
StumplessInitializeProfiles( void )
{
  configuration->profile_count = 0;
  
  profile_array_capacity = 100;
  size_t array_size;
  array_size = profile_array_capacity * sizeof( StumplessCustomProfile );
  configuration->profiles = malloc( array_size );
  if( configuration->profiles == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  StumplessCustomProfile * profile;
  
  ADD_PROFILE( "Short", Short )
  
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessSetConfiguration( StumplessConfiguration * new_configuration )
{
  if( configuration == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  configuration = new_configuration;
  return STUMPLESS_SUCCESS;
}
