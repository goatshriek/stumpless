#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/level.h"
#include "private/output.h"
#include "private/type.h"

#include "private/formatter/text.h"

#include "private/container/list/value.h"

#define LEVEL_FUNCTION( function_name, level_name, level_value )               \
Level *                                                                        \
Get##function_name##Level( void )                                              \
{                                                                              \
  Level * level_name = malloc( sizeof( Level ) );                              \
  if( level_name == NULL )                                                     \
    return NULL;                                                               \
                                                                               \
  level_name->value = level_value;                                             \
  level_name->name = #level_name;                                              \
                                                                               \
  return level_name;                                                           \
}

LEVEL_FUNCTION( Alert, alert, 0 )

LEVEL_FUNCTION( Critical, critical, 0 )

LEVEL_FUNCTION( Debug, debug, 30 )

LEVEL_FUNCTION( Emergency, emergency, 0 )

LEVEL_FUNCTION( Error, error, 10 )

LEVEL_FUNCTION( Fatal, fatal, 0 )

LEVEL_FUNCTION( Info, info, 40 )

LEVEL_FUNCTION( Notice, notice, 0 )

LEVEL_FUNCTION( Warning, warning, 20 )

char *
LevelToString( Level * level )
{
  Output * output = LevelToText( level );
  return OutputToString( output );
}
