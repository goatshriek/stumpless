#include <stdlib.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/string_helper.h"
#include "private/type.h"

#include "private/container/list/value.h"

unsigned short
BinaryOutputIsEmpty
( const Output * output )
{
  return 0;
}

char *
BinaryOutputToString
( const Output * output )
{
  return NULL;
}

unsigned short
CSVOutputIsEmpty
( const Output * output )
{
  return 0;
}

char *
CSVOutputToString
( const Output * output )
{
  return NULL;
}

unsigned short
OutputIsEmpty
( const Output * output )
{
  if( !output || !output->profile || !output->profile->is_empty )
    return 1;
  
  return output->profile->is_empty( output );
}

char *
OutputToString
( const Output * output )
{
  if( !output || !output->profile || !output->profile->to_string )
    return NULL;
  
  return output->profile->to_string( output );
}

unsigned short
JSONOutputIsEmpty
( const Output * output )
{
  return 0;
}

char *
JSONOutputToString
( const Output * output )
{
  return NULL;
}

unsigned short
RawStringOutputIsEmpty
( const Output * output )
{
  if( !output || !output->data )
    return 1;
  
  return ( output->data->c_p == NULL );
}

char *
RawStringOutputToString
( const Output * output )
{
  if( !output || !output->data || !output->data->c_p )
    return NULL;
  
  return copy_string( output->data->c_p );
}

unsigned short
TextOutputIsEmpty
( const Output * output )
{
  if( !output || !output->data )
    return 1;
  
  ValueList * list = ( ValueList * ) output->data->v_p;
  
  return ValueListIsEmpty( list );
}

char *
TextOutputToString
( const Output * output )
{
  if( !output || !output->data )
    return NULL;
  
  ValueList * list = ( ValueList * ) output->data->v_p;
  
  return ValueListToString( list );
}

unsigned short
XMLOutputIsEmpty
( const Output * output )
{
  return 0;
}

char *
XMLOutputToString
( const Output * output )
{
  return NULL;
}
