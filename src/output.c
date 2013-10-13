#include <stdlib.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/string_helper.h"
#include "private/type.h"
#include "private/value_list.h"

unsigned short
BinaryOutputIsEmpty
( Output * output )
{
  return 0;
}

char *
BinaryOutputToString
( Output * output )
{
  return NULL;
}

unsigned short
CSVOutputIsEmpty
( Output * output )
{
  return 0;
}

char *
CSVOutputToString
( Output * output )
{
  return NULL;
}

unsigned short
OutputIsEmpty
( Output * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->is_empty == NULL )
    return 1;
  
  return output->profile->is_empty( output );
}

char *
OutputToString
( Output * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->to_string == NULL )
    return NULL;
  
  return output->profile->to_string( output );
}

unsigned short
JSONOutputIsEmpty
( Output * output )
{
  return 0;
}

char *
JSONOutputToString
( Output * output )
{
  return NULL;
}

unsigned short
RawStringOutputIsEmpty
( Output * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  return ( output->data->c_p == NULL );
}

char *
RawStringOutputToString
( Output * output )
{
  if( output == NULL || output->data == NULL || output->data->c_p == NULL )
    return NULL;
  
  return copy_string( output->data->c_p );
}

unsigned short
TextOutputIsEmpty
( Output * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  ValueList * list = ( ValueList * ) output->data;
  
  return ValueListIsEmpty( list );
}

char *
TextOutputToString
( Output * output )
{
  if( output == NULL || output->data == NULL )
    return NULL;
  
  ValueList * list = ( ValueList * ) output->data;
  
  return ValueListToString( list );
}

unsigned short
XMLOutputIsEmpty
( Output * output )
{
  return 0;
}

char *
XMLOutputToString
( Output * output )
{
  return NULL;
}
