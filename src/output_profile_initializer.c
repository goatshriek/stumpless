#include <stdlib.h>

#include "private/dictionary.h"
#include "private/output.h"
#include "private/output_profile.h"
#include "private/output_profile_initializer.h"
#include "private/status.h"
#include "private/type.h"

#include "private/handler/stream.h"

#define ADD_PROFILE( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##OutputProfile );

#define PROFILE_INITIALIZER( profile_name, type_name )                         \
OutputProfile *                                                                \
Initialize##type_name##OutputProfile                                           \
( void )                                                                       \
{                                                                              \
  OutputProfile * profile = malloc( sizeof( OutputProfile ) );                 \
  if( !profile )                                                               \
    return NULL;                                                               \
                                                                               \
  profile->into_buffer = NULL;                                                 \
  profile->into_http = NULL;                                                   \
  profile->into_mysql = NULL;                                                  \
  profile->into_stream = type_name##OutputIntoStream;                          \
  profile->into_string = NULL;                                                 \
  profile->into_tcp = NULL;                                                    \
  profile->is_empty = type_name##OutputIsEmpty;                                \
  profile->name = profile_name;                                                \
  profile->to_string = type_name##OutputToString;                              \
                                                                               \
  return profile;                                                              \
}

static Dictionary * initializers = NULL;

Status *
InitializeOutputProfileByName
( const char * name )
{
  if( !initializers ){
    
    initializers = NewDictionary();
    if( !initializers )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_PROFILE( "raw string", RawString )
    ADD_PROFILE( "text", Text )
  }
  
  OutputProfile * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( !initializer )
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
