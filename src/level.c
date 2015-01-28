#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/exception.h>
#include <stumpless/formatter/text.h>

#include "private/container/dictionary.h"
#include "private/container/list/value.h"
#include "private/formatter.h"
#include "private/level.h"
#include "private/level/initializer.h"
#include "private/output.h"
#include "private/type.h"

static Dictionary *levels = NULL; /**< currently initialized levels (by name) */

Exception *
AddLevel
( Level *level )
{
  if( !level || !level->name )
    return NULL;

  if( !levels ){
    levels = NewDictionary();

    if( !levels )
      return RaiseException( "constructor failure" );
  }

  if( !SetDictionaryValue( levels, level->name, level ) )
    return RaiseException( "dictionary failure" );

  return NULL;
}

Level *
FindLevelByName
( const char *name )
{
  Level *level;

  if( !levels ){
    levels = NewDictionary();

    if( !levels )
      return NULL;
  }

  level = GetDictionaryValue( levels, name );

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
  return OutputToString( LevelToText( FindFormatterByName( "text" ), level ) );
}
