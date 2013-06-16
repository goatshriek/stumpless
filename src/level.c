#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <formatted_output.h>
#include <level.h>
#include <text_formatter.h>
#include <type.h>
#include <value_list.h>

#define STUMPLESS_LEVEL_FUNCTION( function_name, level_name, level_value )     \
StumplessLevel *                                                               \
StumplessGet##function_name##Level( void )                                     \
{                                                                              \
  StumplessLevel * level_name = malloc( sizeof( StumplessLevel ) );            \
  if( level_name == NULL )                                                     \
    return NULL;                                                               \
                                                                               \
  level_name->value = level_value;                                             \
  level_name->name = #level_name;                                              \
                                                                               \
  return level_name;                                                           \
}

STUMPLESS_LEVEL_FUNCTION( Alert, alert, 0 )

STUMPLESS_LEVEL_FUNCTION( Critical, critical, 0 )

STUMPLESS_LEVEL_FUNCTION( Debug, debug, 30 )

STUMPLESS_LEVEL_FUNCTION( Emergencty, emergency, 0 )

STUMPLESS_LEVEL_FUNCTION( Error, error, 10 )

STUMPLESS_LEVEL_FUNCTION( Fatal, fatal, 0 )

STUMPLESS_LEVEL_FUNCTION( Info, info, 40 )

STUMPLESS_LEVEL_FUNCTION( Notice, notice, 0 )

STUMPLESS_LEVEL_FUNCTION( Warning, warning, 20 )

char *
StumplessLevelToString( StumplessLevel * level )
{
  StumplessFormattedOutput * output = StumplessLevelToText( level );
  return StumplessFormattedOutputToString( output );
}
