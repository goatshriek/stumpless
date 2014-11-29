#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/level.h"
#include "private/level/initializer.h"
#include "private/status.h"

#define NEW_LEVEL_FUNCTION( level_name, function_name, level_value )           \
Level *                                                                        \
New##function_name##Level                                                      \
( void )                                                                       \
{                                                                              \
  Level *level = malloc( sizeof( Level ) );                                    \
  if( !level )                                                                 \
    return NULL;                                                               \
                                                                               \
  level->name = level_name;                                                    \
  level->primary = level_value ;                                               \
  level->secondary = 0;                                                        \
  level->tertiary = 0;                                                         \
                                                                               \
  return level;                                                                \
}

#define ADD_LEVEL( name, function )                                            \
SetDictionaryValue( initializers, name, New##function##Level );

static Dictionary *initializers = NULL;

Status *
InitializeLevelByName
( const char *name )
{
  Level *( *initializer )();

  if( !initializers ){
    initializers = NewDictionary();
    if( !initializers )
      return RaiseStatus( "constructor failure" );

    ADD_LEVEL( "alert", Alert )
    ADD_LEVEL( "critical", Critical )
    ADD_LEVEL( "debug", Debug )
    ADD_LEVEL( "emergency", Emergency )
    ADD_LEVEL( "error", Error )
    ADD_LEVEL( "informational", Informational )
    ADD_LEVEL( "notice", Notice )
    ADD_LEVEL( "warning", Warning )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer )
    return NULL;
  else
    return AddLevel( initializer() );
}

NEW_LEVEL_FUNCTION( "alert", Alert, 1 )

NEW_LEVEL_FUNCTION( "critical", Critical, 2 )

NEW_LEVEL_FUNCTION( "debug", Debug, 7 )

NEW_LEVEL_FUNCTION( "emergency", Emergency, 0 )

NEW_LEVEL_FUNCTION( "error", Error, 3 )

NEW_LEVEL_FUNCTION( "informational", Informational, 6 )

NEW_LEVEL_FUNCTION( "notice", Notice, 5 )

NEW_LEVEL_FUNCTION( "warning", Warning, 4 )
