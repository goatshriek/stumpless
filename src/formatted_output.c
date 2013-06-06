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
  if( output == NULL || output->profile == NULL
   || output->profile->to_string == NULL )
    return NULL;
  
  return output->profile->to_string( output );
}
