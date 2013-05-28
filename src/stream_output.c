#include <stdio.h>
#include <stdlib.h>

#include <stream_output.h>
#include <type.h>

StumplessStatusCode
StumplessTextOutputToStream( FILE * file, StumplessFormattedOutput * output )
{
  if( file == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( output->payload == NULL || output->payload->values == NULL )
    return STUMPLESS_MALFORMED_STRUCTURE;
  
  // todo need to implement
  
  return STUMPLESS_SUCCESS;
}
