#include <configuration.h>
#include <formatted_output.h>
#include <type.h>
#include <value_list.h>

unsigned short
StumplessBinaryFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  return 0;
}

char *
StumplessBinaryFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

unsigned short
StumplessCSVFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  return 0;
}

char *
StumplessCSVFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->is_empty == NULL )
    return 1;
  
  return output->profile->is_empty( output );
}

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL || output->profile == NULL
   || output->profile->to_string == NULL )
    return NULL;
  
  return output->profile->to_string( output );
}

unsigned short
StumplessJSONFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  return 0;
}

char *
StumplessJSONFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}

unsigned short
StumplessTextFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  return ( output == NULL || output->payload == NULL
        || StumplessValueListIsEmpty( output->payload->values ) );
}

char *
StumplessTextFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL || output->payload == NULL )
    return NULL;
  
  return StumplessValueListToString( output->payload->values );
}

unsigned short
StumplessXMLFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  return 0;
}

char *
StumplessXMLFormattedOutputToString( StumplessFormattedOutput * output )
{
  return NULL;
}
