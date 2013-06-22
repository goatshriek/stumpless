#include <stdlib.h>

#include <configuration.h>
#include <formatted_output.h>
#include <string_helper.h>
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
StumplessRawTextFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  return ( output->data->c_p == NULL );
}

char *
StumplessRawTextFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL || output->data == NULL || output->data->c_p == NULL )
    return NULL;
  
  return copy_string( output->data->c_p );
}

unsigned short
StumplessTextFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return 1;
  
  StumplessValueList * list = ( StumplessValueList * ) output->data;
  
  return StumplessValueListIsEmpty( list );
}

char *
StumplessTextFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL || output->data == NULL )
    return NULL;
  
  StumplessValueList * list = ( StumplessValueList * ) output->data;
  
  return StumplessValueListToString( list );
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
