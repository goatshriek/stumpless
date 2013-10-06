#include <stdio.h>
#include <stdlib.h>

#include "private/status.h"
#include "private/stream_output.h"
#include "private/type.h"

Status *
BinaryFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
CSVFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
JSONFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
RawStringFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}

Status *
TextFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  if( output == NULL || file == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  // todo need to implement
  
  return NULL;
}

Status *
XMLFormattedOutputIntoStream
( FormattedOutput * output, FILE * file )
{
  // todo need to implement
  
  return NULL;
}
