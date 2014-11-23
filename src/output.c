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

void
DestroyOutput
( Output *output )
{
  if( !output )
    return;

  free( output->data );
  free( output );

  return;
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

  return ( output->data == NULL );
}

char *
RawStringOutputToString
( const Output *output )
{
  if( !output || !output->data )
    return NULL;

  return ValueToString( output->data );
}

unsigned short
TextOutputIsEmpty
( const Output * output )
{
  if( !output )
    return 1;

  return ValueListIsEmpty( output->data );
}

char *
TextOutputToString
( const Output * output )
{
  if( !output )
    return NULL;

  return ValueListToString( output->data );
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
