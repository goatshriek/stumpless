#include <configuration.h>
#include <formatted_output.h>
#include <type.h>

StumplessStatusCode
StumplessFormattedOutputIntoString( char * str,
                                    StumplessFormattedOutput * output )
{
  if( str == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  // todo need to implement this functionality
  //switch( output->format ){
  //  case STUMPLESS_TEXT:
  //    return StumplessValueListIntoString( str, output->payload->values );
  //  default:
  //    return STUMPLESS_FAILURE;
  //}
  
  return STUMPLESS_SUCCESS;
}

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  if( output == NULL || output->payload == NULL )
    return 1;
  
  // todo replace this functionality somehow
  //switch( output->format ){
  //  case STUMPLESS_TEXT:
  //    return StumplessValueListIsEmpty( output->payload->values );
  //}
  return 0;
}

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  if( configuration == NULL )
    return NULL;
  
  size_t buffer_size = configuration->string->buffer_size;
  char * str = malloc( sizeof( char ) * buffer_size );
  if( str == NULL )
    return NULL;
  
  status = StumplessFormattedOutputIntoString( str, output );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  else
    return str;
}
