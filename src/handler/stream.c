#include <stdio.h>
#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/handler/stream.h"
#include "private/type.h"

const Output *
BinaryOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return output;
}

const Output *
CSVOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return output;
}

const Handler *
HandleStreamOutput
( const Handler *handler, const Output *output )
{
  FILE *destination;

  if( !output )
    return handler;

  // todo throw malformed profile exception here
  if( !output->profile || !output->profile->into_stream )
    return handler;

  // todo this should go away eventually to read the handler
  destination = stdout;

  output->profile->into_stream( output, destination );
  return handler;
}

const Output *
JSONOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return output;
}

const Output *
RawStringOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return output;

  // todo throw malformed structure Exception here
  if( !output->data )
    return output;

  // todo throw stream write failure exception here
  if( fputs( ValueListToString( output->data ), stream ) < 0 )
    return output;

  return output;
}

const Output *
TextOutputIntoStream
( const Output *output, FILE *stream )
{
  if( !output || !stream )
    return output;

  // todo throw malformed structure Exception here
  if( !output->data )
    return output;;

  fputs( ValueListToString( output->data ), stream );

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

  return output;
}

const Output *
XMLOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement

  return output;
}
