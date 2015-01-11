#include <stdio.h>
#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/handler/stream.h"
#include "private/type.h"

Exception *
BinaryOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Exception *
CSVOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Exception *
HandleStreamOutput
( const Handler *handler, const Output *output )
{
  FILE *destination;

  if( !output )
    return RaiseException( "empty argument" );

  if( !output->profile || !output->profile->into_stream )
    return RaiseException( "incompatible profile" );

  destination = stdout;

  return output->profile->into_stream( output, destination );
}

Exception *
JSONOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}

Exception *
RawStringOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return RaiseException( "empty argument" );

  if( !output->data )
    return RaiseException( "malformed structure" );

  if( fputs( ValueListToString( output->data ), stream ) < 0 )
    return RaiseException( "stream write failure" );

  return NULL;
}

Exception *
TextOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return RaiseException( "empty argument" );

  if( !output->data )
    return RaiseException( "malformed structure" );

  fputs( ValueListToString( output->data ), stream );
  return NULL;

  /*const Value *value;
  ValueListConstIterator * values = CBeginValueList( output->data );
  while( value = NextInValueListConstIterator( values ) ){
    if( !value->data ){
      DestroyValueListConstIterator( values );
      return RaiseException( "malformed structure" );
    }

    if( fputs( value->data->c_p, stream ) < 0 ){
      DestroyValueListConstIterator( values );
      return RaiseException( "stream write failure" );
    }
  }

  DestroyValueListConstIterator( values );*/

  return NULL;
}

Exception *
XMLOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return NULL;
}
