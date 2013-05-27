#include <stdlib.h>

#include <configuration.h>
#include <status_checker.h>
#include <text_formatter.h>
#include <type.h>
#include <value.h>

#define ADD_ARRAY_VALUE_PROFILE( profile_name, type_name )                     \
profile = malloc( sizeof( StumplessValueProfile ) );                           \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->into_string = NULL;                                                   \
profile->name = profile_name;                                                  \
profile->to_binary = NULL;                                                     \
profile->to_csv = NULL;                                                        \
profile->to_json = NULL;                                                       \
profile->to_string = NULL;                                                     \
profile->to_text = &StumplessGenericArrayValueToText;                          \
profile->to_value_list = &Stumpless##type_name##ValueToValueList;              \
profile->to_xml = NULL;                                                        \
StumplessAddValueProfile( profile );

#define ADD_OUTPUT_PROFILE( profile_name, type_name )                          \
profile = malloc( sizeof( StumplessOutputProfile ) );                          \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->to_http = NULL;                                                       \
profile->name = profile_name;                                                  \
profile->to_mysql = NULL;                                                      \
profile->to_stream = NULL;                                                     \
profile->to_tcp = NULL;                                                        \
StumplessAddOutputProfile( profile );

#define ADD_SINGLE_VALUE_PROFILE( profile_name, type_name )                    \
profile = malloc( sizeof( StumplessValueProfile ) );                           \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->into_string = &Stumpless##type_name##ValueIntoString;                 \
profile->name = profile_name;                                                  \
profile->to_binary = NULL;                                                     \
profile->to_csv = NULL;                                                        \
profile->to_json = NULL;                                                       \
profile->to_string = &Stumpless##type_name##ValueToString;                     \
profile->to_text = &StumplessGenericValueToText;                               \
profile->to_value_list = &StumplessGenericValueToValueList;                    \
profile->to_xml = NULL;                                                        \
StumplessAddValueProfile( profile );

static StumplessConfiguration * configuration = NULL;
static unsigned output_profile_array_capacity = 0;
static unsigned value_profile_array_capacity = 0;

StumplessStatusCode
StumplessAddOutputProfile( StumplessOutputProfile * profile )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  unsigned index = configuration->output_profile_count;
  
  configuration->output_profiles[index] = profile;
  configuration->output_profile_count++;
  
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessAddValueProfile( StumplessValueProfile * profile )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  unsigned index = configuration->value_profile_count;
  
  configuration->value_profiles[index] = profile;
  configuration->value_profile_count++;
  
  return STUMPLESS_SUCCESS;
}

StumplessOutputProfile *
StumplessFindOutputProfileByName( const char * name )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  unsigned i;
  for( i = 0; i < configuration->output_profile_count; i++ )
    if( strcmp( configuration->output_profiles[i]->name, name ) == 0 )
      return configuration->output_profiles[i];
  
  return NULL;
}

StumplessValueProfile *
StumplessFindValueProfileByName( const char * name )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  unsigned i;
  for( i = 0; i < configuration->value_profile_count; i++ )
    if( strcmp( configuration->value_profiles[i]->name, name ) == 0 )
      return configuration->value_profiles[i];
  
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

  STATUS_ON_FAILURE( StumplessInitializeValueProfiles() )

  return StumplessInitializeOutputProfiles();
}

StumplessStatusCode
StumplessInitializeOutputProfiles( void )
{
  configuration->output_profile_count = 0;
  
  output_profile_array_capacity = 100;
  size_t array_size;
  array_size = output_profile_array_capacity * sizeof( StumplessOutputProfile );
  configuration->output_profiles = malloc( array_size );
  if( configuration->output_profiles == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  StumplessOutputProfile * profile;
  
  ADD_OUTPUT_PROFILE( "HTTP", Stream )
  ADD_OUTPUT_PROFILE( "Stream", Stream )
  ADD_OUTPUT_PROFILE( "String", Stream )
  ADD_OUTPUT_PROFILE( "TCP", Stream )
  
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessInitializeValueProfiles( void )
{
  configuration->value_profile_count = 0;
  
  value_profile_array_capacity = 100;
  size_t array_size;
  array_size = value_profile_array_capacity * sizeof( StumplessValueProfile );
  configuration->value_profiles = malloc( array_size );
  if( configuration->value_profiles == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  StumplessValueProfile * profile;
  
  ADD_ARRAY_VALUE_PROFILE( "Boolean Array", BooleanArray )
  ADD_ARRAY_VALUE_PROFILE( "Char Array", CharArray )
  ADD_ARRAY_VALUE_PROFILE( "Float Array", FloatArray )
  ADD_ARRAY_VALUE_PROFILE( "Double Array", DoubleArray )
  ADD_ARRAY_VALUE_PROFILE( "Int Array", IntArray )
  ADD_ARRAY_VALUE_PROFILE( "Long Array", LongArray )
  ADD_ARRAY_VALUE_PROFILE( "Long Double Array", LongDoubleArray )
  ADD_ARRAY_VALUE_PROFILE( "Long Long Array", LongLongArray )
  ADD_ARRAY_VALUE_PROFILE( "Short Array", ShortArray )
  ADD_ARRAY_VALUE_PROFILE( "Signed Char Array", SignedCharArray )
  ADD_ARRAY_VALUE_PROFILE( "String Array", StringArray )
  ADD_ARRAY_VALUE_PROFILE( "Unsigned Char Array", UnsignedCharArray )
  ADD_ARRAY_VALUE_PROFILE( "Unsigned Int Array", UnsignedIntArray )
  ADD_ARRAY_VALUE_PROFILE( "Unsigned Long Array", UnsignedLongArray )
  ADD_ARRAY_VALUE_PROFILE( "Unsigned Long Long Array", UnsignedLongLongArray )
  ADD_ARRAY_VALUE_PROFILE( "Unsigned Short Array", UnsignedShortArray )
  
  ADD_SINGLE_VALUE_PROFILE( "Boolean", Boolean )
  ADD_SINGLE_VALUE_PROFILE( "Char", Char )
  ADD_SINGLE_VALUE_PROFILE( "Float", Float )
  ADD_SINGLE_VALUE_PROFILE( "Double", Double )
  ADD_SINGLE_VALUE_PROFILE( "Int", Int )
  ADD_SINGLE_VALUE_PROFILE( "Long", Long )
  ADD_SINGLE_VALUE_PROFILE( "Long Double", LongDouble )
  ADD_SINGLE_VALUE_PROFILE( "Long Long", LongLong )
  ADD_SINGLE_VALUE_PROFILE( "Short", Short )
  ADD_SINGLE_VALUE_PROFILE( "Signed Char", SignedChar )
  ADD_SINGLE_VALUE_PROFILE( "String", String )
  ADD_SINGLE_VALUE_PROFILE( "Unsigned Char", UnsignedChar )
  ADD_SINGLE_VALUE_PROFILE( "Unsigned Int", UnsignedInt )
  ADD_SINGLE_VALUE_PROFILE( "Unsigned Long", UnsignedLong )
  ADD_SINGLE_VALUE_PROFILE( "Unsigned Long Long", UnsignedLongLong )
  ADD_SINGLE_VALUE_PROFILE( "Unsigned Short", UnsignedShort )
  
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
