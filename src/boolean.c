#include <stdlib.h>

#include <boolean.h>
#include <string_helper.h>
#include <type.h>

char *
StumplessBooleanToString( StumplessBoolean * boolean )
{
  if( boolean == NULL )
    return NULL;
  
  if( boolean->value )
    return copy_string( boolean->format->true_description );
  else
    return copy_string( boolean->format->false_description );
}
