#include <stdio.h>
#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/handler/stream.h"
#include "private/type.h"

FILE *
BinaryOutputIntoStream
( FILE *stream,  const Output *output )
{
  // todo need to implement

  return stream;
}

FILE *
CSVOutputIntoStream
( FILE *stream, const Output *output )
{
  // todo need to implement

  return stream;
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

  output->profile->into_stream( destination, output );
  return handler;
}

FILE *
JSONOutputIntoStream
( FILE *stream, const Output *output )
{
  // todo need to implement

  return stream;
}

FILE *
RawStringOutputIntoStream
( FILE *stream, const Output *output )
{
  if( !output || !stream )
    return stream;

  // todo throw malformed structure Exception here
  if( !output->data )
    return stream;

  // todo throw stream write failure exception here
  if( fputs( ValueListToString( output->data ), stream ) < 0 )
    return stream;

  return stream;
}

FILE *
TextOutputIntoStream
( FILE *stream, const Output *output )
{
  if( !output || !stream )
    return stream;

  // todo throw malformed structure Exception here
  if( !output->data )
    return stream;

  fputs( ValueListToString( output->data ), stream );

  return stream;
}

FILE *
XMLOutputIntoStream
( FILE *stream, const Output *output )
{
  // todo need to implement

  return stream;
}
