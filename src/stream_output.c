#include <stdio.h>
#include <stdlib.h>

#include "private/status.h"
#include "private/stream_output.h"
#include "private/type.h"

Status *
TextOutputToStream( FILE * file, FormattedOutput * output )
{
  if( file == NULL || output == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  // todo need to implement
  
  return NULL;
}
