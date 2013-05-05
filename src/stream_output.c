#include <stdio.h>
#include <stdlib.h>

#include <stream_output.h>
#include <type.h>

StumplessStatusCode
StumplessWriteToStream( FILE * file, StumplessFormattedOutput * output )
{
  if( file == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  return STUMPLESS_FAILURE;
}
