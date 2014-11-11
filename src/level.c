#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/container/dictionary.h"
#include "private/container/list/value.h"
#include "private/formatter/text.h"
#include "private/level.h"
#include "private/level/initializer.h"
#include "private/output.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary *levels = NULL; /**< currently initialized levels (by name) */

Status *
AddLevel
( Level *level )
{
  if( !level || !level->name )
    return RaiseStatus( "empty argument" );
  
  if( !levels ){
    levels = NewDictionary();
    
    if( !levels )
      return RaiseStatus( "constructor failure" );
  }

  if( !SetDictionaryValue( levels, level->name, level ) )
    return RaiseStatus( "dictionary failure" );

  return NULL;
}

Level *
FindLevelByName
( const char *name )
{
  if( !levels ){
    levels = NewDictionary();
    
    if( !levels )
      return NULL;
  }
  
  Level *level = GetDictionaryValue( levels, name );

  if( !level ){
    if( InitializeLevelByName( name ) )
      return NULL;
    level = GetDictionaryValue( levels, name );
  }

  return level;
}

char *
LevelToString
( const Level *level )
{
  return OutputToString( LevelToText( level ) );
}
