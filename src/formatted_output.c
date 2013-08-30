#include <stdlib.h>

#include "private/configuration.h"
#include "private/formatted_output.h"
#include "private/string_helper.h"
#include "private/type.h"
#include "private/value_list.h"

unsigned short
BinaryFormattedOutputIsEmpty
( FormattedOutput * output )
{
  return 0;
}

char *
BinaryFormattedOutputToString
( FormattedOutput * output )
{
  return NULL;
}

unsigned short
CSVFormattedOutputIsEmpty
( FormattedOutput * output )
{
  return 0;
}

char *
CSVFormattedOutputToString
( FormattedOutput * output )
{
  return NULL;
}

unsigned short
FormattedOutputIsEmpty
( FormattedOutput * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->is_empty == NULL )
    return 1;
  
  return output->profile->is_empty( output );
}

char *
FormattedOutputToString
( FormattedOutput * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->to_string == NULL )
    return NULL;
  
  return output->profile->to_string( output );
}

unsigned short
JSONFormattedOutputIsEmpty
( FormattedOutput * output )
{
  return 0;
}

char *
JSONFormattedOutputToString
( FormattedOutput * output )
{
  return NULL;
}

unsigned short
RawStringFormattedOutputIsEmpty
( FormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  return ( output->data->c_p == NULL );
}

char *
RawStringFormattedOutputToString
( FormattedOutput * output )
{
  if( output == NULL || output->data == NULL || output->data->c_p == NULL )
    return NULL;
  
  return copy_string( output->data->c_p );
}

unsigned short
TextFormattedOutputIsEmpty
( FormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  ValueList * list = ( ValueList * ) output->data;
  
  return ValueListIsEmpty( list );
}

char *
TextFormattedOutputToString
( FormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return NULL;
  
  ValueList * list = ( ValueList * ) output->data;
  
  return ValueListToString( list );
}

unsigned short
XMLFormattedOutputIsEmpty
( FormattedOutput * output )
{
  return 0;
}

char *
XMLFormattedOutputToString
( FormattedOutput * output )
{
  return NULL;
}
