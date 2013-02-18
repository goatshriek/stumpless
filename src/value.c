#include <stdlib.h>
#include <string.h>

#include <types.h>
#include <value.h>

StumplessValue *
StumplessValueFromString( char * str )
{
  if( str == NULL )
    return NULL;
  
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->type = STUMPLESS_CHAR_POINTER;
  value->data->c_p = str;
  value->length = strlen( str ) + 1;
  
  return value;
}
