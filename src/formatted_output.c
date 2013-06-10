#include <configuration.h>
#include <formatted_output.h>
#include <type.h>

char *
StumplessBinaryFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

char *
StumplessCSVFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
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

char *
StumplessJSONFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

char *
StumplessTextFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

char *
StumplessXMLFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}
