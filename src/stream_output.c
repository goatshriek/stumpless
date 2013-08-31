#include <stdio.h>
#include <stdlib.h>

#include "private/stream_output.h"
#include "private/type.h"

StatusCode
TextOutputToStream( FILE * file, FormattedOutput * output )
{
  if( file == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  // todo need to implement
  
  return STUMPLESS_SUCCESS;
}
