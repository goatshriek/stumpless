#include <stdlib.h>

#include <configuration.h>
#include <status_checker.h>
#include <text_formatter.h>
#include <type.h>
#include <value.h>

#define ADD_ARRAY_VALUE_PROFILE( profile_name, type_name )                     \
profile = malloc( sizeof( StumplessTypeProfile ) );                            \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->name = profile_name;                                                  \
profile->value_list_converter = &Stumpless##type_name##ValueAsValueList;       \
profile->binary_formatter = NULL;                                              \
profile->csv_formatter = NULL;                                                 \
profile->json_formatter = NULL;                                                \
profile->text_formatter = &StumplessGenericArrayValueAsText;                   \
profile->xml_formatter = NULL;                                                 \
StumplessAddTypeProfile( profile );

#define ADD_SINGLE_VALUE_PROFILE( profile_name, type_name )                    \
profile = malloc( sizeof( StumplessTypeProfile ) );                            \
if( profile == NULL )                                                          \
  return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                  \
profile->name = profile_name;                                                  \
profile->value_list_converter = NULL;                                          \
profile->binary_formatter = NULL;                                              \
profile->csv_formatter = NULL;                                                 \
profile->json_formatter = NULL;                                                \
profile->text_formatter = &StumplessGenericValueAsText;                        \
profile->xml_formatter = NULL;                                                 \
StumplessAddTypeProfile( profile );

static StumplessConfiguration * configuration = NULL;
static unsigned profile_array_capacity = 0;

StumplessProfileIndex
StumplessAddTypeProfile( StumplessTypeProfile * profile )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  StumplessProfileIndex index = configuration->profile_count;
  
  configuration->profiles[index] = profile;
  configuration->profile_count++;
  
  return index;
}

StumplessTypeProfile *
StumplessFindProfileByIndex( StumplessProfileIndex index )
{
  if( configuration == NULL )
    StumplessInitializeConfiguration();
  
  if( index >= configuration->profile_count )
    return NULL;
  else
    return configuration->profiles[index];
}

StumplessTypeProfile *
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
  array_size = profile_array_capacity * sizeof( StumplessTypeProfile );
  configuration->profiles = malloc( array_size );
  if( configuration->profiles == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  StumplessTypeProfile * profile;
  
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
