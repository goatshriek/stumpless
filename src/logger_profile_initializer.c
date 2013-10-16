#include <stdlib.h>

#include "private/dictionary.h"
#include "private/logger_profile.h"
#include "private/logger_profile_initializer.h"
#include "private/status.h"
#include "private/stream_handler.h"
#include "private/type.h"

#define ADD_PROFILE( name, function )                                          \
AddValueToDictionary( initializers, name, Initialize##function##LoggerProfile );

#define PROFILE_INITIALIZER( profile_name, type_name )                         \
LoggerProfile *                                                                \
Initialize##type_name##LoggerProfile                                           \
( void )                                                                       \
{                                                                              \
  LoggerProfile * profile = malloc( sizeof( LoggerProfile ) );                 \
  if( profile == NULL )                                                        \
    return NULL;                                                               \
                                                                               \
  return profile;                                                              \
}

static Dictionary * initializers = NULL;

Status *
InitializeLoggerProfileByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  LoggerProfile * ( *initializer )();
  initializer = GetValueFromDictionary( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddLoggerProfile( initializer() );
}
