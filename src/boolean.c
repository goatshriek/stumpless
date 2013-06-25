#include <stdlib.h>

#include "private/boolean.h"
#include "private/string_helper.h"
#include "private/type.h"

char *
BooleanToString( Boolean * boolean )
{
  if( boolean == NULL )
    return NULL;
  
  if( boolean->value )
    return copy_string( boolean->format->true_description );
  else
    return copy_string( boolean->format->false_description );
}
