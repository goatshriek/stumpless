#include <stdlib.h>

#include "private/dictionary.h"
#include "private/formatted_output.h"
#include "private/output_profile.h"
#include "private/output_profile_initializer.h"
#include "private/status.h"
#include "private/stream_output.h"
#include "private/type.h"

#define ADD_PROFILE( name, function )                                          \
AddValueToDictionary( initializers, name, Initialize##function##OutputProfile );

#define PROFILE_INITIALIZER( profile_name, type_name )                         \
OutputProfile *                                                                \
Initialize##type_name##OutputProfile                                           \
( void )                                                                       \
{                                                                              \
  OutputProfile * profile = malloc( sizeof( OutputProfile ) );                 \
  if( profile == NULL )                                                        \
    return NULL;                                                               \
                                                                               \
  profile->into_buffer = NULL;                                                 \
  profile->into_http = NULL;                                                   \
  profile->into_mysql = NULL;                                                  \
  profile->into_stream = type_name##FormattedOutputIntoStream;                 \
  profile->into_string = NULL;                                                 \
  profile->into_tcp = NULL;                                                    \
  profile->is_empty = type_name##FormattedOutputIsEmpty;                       \
  profile->name = profile_name;                                                \
  profile->to_string = type_name##FormattedOutputToString;                     \
                                                                               \
  return profile;                                                              \
}

Dictionary * initializers = NULL;

Status *
InitializeOutputProfileByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_PROFILE( "text", Text )
  }
  
  OutputProfile * ( *initializer )();
  initializer = GetValueFromDictionary( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddOutputProfile( initializer() );
}

PROFILE_INITIALIZER( "binary", Binary )

PROFILE_INITIALIZER( "csv", CSV )

PROFILE_INITIALIZER( "json", JSON )

PROFILE_INITIALIZER( "raw string", RawString )

PROFILE_INITIALIZER( "text", Text )

PROFILE_INITIALIZER( "xml", XML )
