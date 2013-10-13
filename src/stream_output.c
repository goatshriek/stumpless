#include <stdio.h>
#include <stdlib.h>

#include "private/status.h"
#include "private/stream_output.h"
#include "private/type.h"

Status *
BinaryOutputIntoStream
( Output * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
CSVOutputIntoStream
( Output * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
JSONOutputIntoStream
( Output * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
RawStringOutputIntoStream
( Output * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
TextOutputIntoStream
( Output * output, FILE * file )
{
  if( output == NULL || file == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  // todo need to implement
  
  return NULL;
}

Status *
XMLOutputIntoStream
( Output * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}
