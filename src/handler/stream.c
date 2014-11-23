#include <stdio.h>
#include <stdlib.h>

#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/handler/stream.h"
#include "private/status.h"
#include "private/type.h"

Status *
BinaryOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Status *
CSVOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Status *
HandleStreamOutput
( const Handler *handler, const Output * output )
{
  if( !output )
    return RaiseStatus( "empty argument" );

  if( !output->profile || !output->profile->into_stream )
    return RaiseStatus( "incompatible profile" );

  FILE * destination = stdout;

  return output->profile->into_stream( output, destination );
}

Status *
JSONOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Status *
RawStringOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return RaiseStatus( "empty argument" );

  if( !output->data )
    return RaiseStatus( "malformed structure" );

  if( fputs( ValueListToString( output->data ), stream ) < 0 )
    return RaiseStatus( "stream write failure" );

  return NULL;
}

Status *
TextOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return RaiseStatus( "empty argument" );

  if( !output->data )
    return RaiseStatus( "malformed structure" );

  fputs( ValueListToString( output->data ), stream );
  return NULL;

  /*const Value *value;
  ValueListConstIterator * values = CBeginValueList( output->data );
  while( value = NextInValueListConstIterator( values ) ){
    if( !value->data ){
      DestroyValueListConstIterator( values );
      return RaiseStatus( "malformed structure" );
    }

    if( fputs( value->data->c_p, stream ) < 0 ){
      DestroyValueListConstIterator( values );
      return RaiseStatus( "stream write failure" );
    }
  }

  DestroyValueListConstIterator( values );*/

  return NULL;
}

Status *
XMLOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}
