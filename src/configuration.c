#include <stdlib.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/status.h"
#include "private/status_checker.h"
#include "private/text_formatter.h"
#include "private/type.h"
#include "private/value.h"

#define ADD_OUTPUT_PROFILE( profile_name, type_name )                          \
profile = malloc( sizeof( OutputProfile ) );                                   \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->into_buffer = NULL;                                                   \
profile->into_http = NULL;                                                     \
profile->into_mysql = NULL;                                                    \
profile->into_stream = NULL;                                                   \
profile->into_string = NULL;                                                   \
profile->into_tcp = NULL;                                                      \
profile->is_empty = &type_name##OutputIsEmpty;                                 \
profile->name = profile_name;                                                  \
profile->to_string = &type_name##OutputToString;                               \
AddOutputProfile( profile );

static Configuration * configuration = NULL;

// todo an expanding array allocation method can get rid of these
static unsigned logging_profile_array_capacity = 0;

StatusCode
AddLoggingProfile( LoggingProfile * profile )
{
  if( configuration == NULL )
    InitializeConfiguration();
  
  unsigned index = configuration->logging_profile_count;
  
  configuration->logging_profiles[index] = profile;
  configuration->logging_profile_count++;
  
  return STUMPLESS_SUCCESS;
}

LoggingProfile *
FindLoggingProfileByName( const char * name )
{
  if( configuration == NULL )
    InitializeConfiguration();
  
  unsigned i;
  for( i = 0; i < configuration->logging_profile_count; i++ )
    if( strcmp( configuration->logging_profiles[i]->name, name ) == 0 )
      return configuration->logging_profiles[i];
  
  return NULL;
}

Configuration *
GetConfiguration( void )
{
  if( configuration == NULL )
    NULL_ON_FAILURE( InitializeConfiguration() )
  
  return configuration;
}

StatusCode
InitializeConfiguration( void )
{
  configuration = malloc( sizeof( Configuration ) );
  if( configuration == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  size_t required_size = sizeof( FileConfiguration );
  configuration->file = malloc( required_size );
  if( configuration->file == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  required_size = sizeof( HTTPConfiguration );
  configuration->http = malloc( required_size );
  if( configuration->http == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( ThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( configuration->threading == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( SortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( configuration->sorting == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StringConfiguration );
  configuration->string = malloc( required_size );
  if( configuration->string == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  configuration->string->buffer_size = 100;
  
  return InitializeLoggingProfiles();
}

StatusCode
InitializeLoggingProfiles( void )
{
  if( configuration == NULL )
    return STUMPLESS_INCORRECT_INTERNAL_STATE;
  
  configuration->logging_profile_count = 0;
  
  logging_profile_array_capacity = 100;
  size_t profile_size = sizeof( LoggingProfile );
  size_t array_size = logging_profile_array_capacity * profile_size;
  
  configuration->logging_profiles = malloc( array_size );
  if( configuration->logging_profiles == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  return STUMPLESS_SUCCESS;
}

Status*
SetConfiguration( Configuration * new_configuration )
{
  if( configuration == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  configuration = new_configuration;
  return NULL;
}
