#include <file_output.h>
#include <types.h>

StumplessStatusCode
StumplessWriteToFile( FILE * file, StumplessFormattedOutput * output )
{
  if( file == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  return STUMPLESS_FAILURE;
}
