#include <stdlib.h>

#include <configuration.h>
#include <formatted_output.h>
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
profile->into_buffer = NULL;                                                   \
profile->into_http = NULL;                                                     \
profile->into_mysql = NULL;                                                    \
profile->into_stream = NULL;                                                   \
profile->into_string = NULL;                                                   \
profile->into_tcp = NULL;                                                      \
profile->is_empty = &Stumpless##type_name##FormattedOutputIsEmpty;             \
profile->name = profile_name;                                                  \
profile->to_string = &Stumpless##type_name##FormattedOutputToString;           \
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
  
  required_size = sizeof( StumplessThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( configuration->threading == NULL )
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
  
  ADD_OUTPUT_PROFILE( "binary", Binary )
  ADD_OUTPUT_PROFILE( "csv", CSV )
  ADD_OUTPUT_PROFILE( "json", JSON )
  ADD_OUTPUT_PROFILE( "text", Text )
  ADD_OUTPUT_PROFILE( "xml", XML )
  
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
  
  ADD_ARRAY_VALUE_PROFILE( "boolean array", BooleanArray )
  ADD_ARRAY_VALUE_PROFILE( "char array", CharArray )
  ADD_ARRAY_VALUE_PROFILE( "float array", FloatArray )
  ADD_ARRAY_VALUE_PROFILE( "aouble array", DoubleArray )
  ADD_ARRAY_VALUE_PROFILE( "int array", IntArray )
  ADD_ARRAY_VALUE_PROFILE( "long array", LongArray )
  ADD_ARRAY_VALUE_PROFILE( "long double array", LongDoubleArray )
  ADD_ARRAY_VALUE_PROFILE( "long long array", LongLongArray )
  ADD_ARRAY_VALUE_PROFILE( "short array", ShortArray )
  ADD_ARRAY_VALUE_PROFILE( "signed char array", SignedCharArray )
  ADD_ARRAY_VALUE_PROFILE( "string array", StringArray )
  ADD_ARRAY_VALUE_PROFILE( "unsigned char array", UnsignedCharArray )
  ADD_ARRAY_VALUE_PROFILE( "unsigned int array", UnsignedIntArray )
  ADD_ARRAY_VALUE_PROFILE( "unsigned long array", UnsignedLongArray )
  ADD_ARRAY_VALUE_PROFILE( "unsigned long long array", UnsignedLongLongArray )
  ADD_ARRAY_VALUE_PROFILE( "unsigned short array", UnsignedShortArray )
  
  ADD_SINGLE_VALUE_PROFILE( "boolean", Boolean )
  ADD_SINGLE_VALUE_PROFILE( "char", Char )
  ADD_SINGLE_VALUE_PROFILE( "float", Float )
  ADD_SINGLE_VALUE_PROFILE( "double", Double )
  ADD_SINGLE_VALUE_PROFILE( "int", Int )
  ADD_SINGLE_VALUE_PROFILE( "long", Long )
  ADD_SINGLE_VALUE_PROFILE( "long double", LongDouble )
  ADD_SINGLE_VALUE_PROFILE( "long long", LongLong )
  ADD_SINGLE_VALUE_PROFILE( "short", Short )
  ADD_SINGLE_VALUE_PROFILE( "signed char", SignedChar )
  ADD_SINGLE_VALUE_PROFILE( "string", String )
  ADD_SINGLE_VALUE_PROFILE( "unsigned char", UnsignedChar )
  ADD_SINGLE_VALUE_PROFILE( "unsigned int", UnsignedInt )
  ADD_SINGLE_VALUE_PROFILE( "unsigned long", UnsignedLong )
  ADD_SINGLE_VALUE_PROFILE( "unsigned long long", UnsignedLongLong )
  ADD_SINGLE_VALUE_PROFILE( "unsigned short", UnsignedShort )
  
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
