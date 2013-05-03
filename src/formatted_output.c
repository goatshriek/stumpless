#include <configuration.h>
#include <formatted_output.h>
#include <types.h>

StumplessStatusCode
StumplessAppendFormattedOutputs( StumplessFormattedOutput * beginning,
                                 StumplessFormattedOutput * end )
{
  if( beginning == NULL || end == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( beginning->format != end->format )
    return STUMPLESS_INCOMPATIBLE_ARGUMENTS;
  
  switch( beginning->format ){
    case STUMPLESS_TEXT:
      return StumplessAppendValueLists( beginning->payload->values,
                                        end->payload->values );
    default:
      return STUMPLESS_FAILURE;
  }
}

StumplessStatusCode
StumplessAppendStringToFormattedOutput( StumplessFormattedOutput * output,
                                        const char * str )
{
  if( output == NULL || str == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  switch( output->format ){
    case STUMPLESS_TEXT:
      return StumplessAppendStringToValueList( output->payload->values, str );
    default:
      return STUMPLESS_FAILURE;
  }
}

StumplessStatusCode
StumplessAppendUnsignedIntToFormattedOutput( StumplessFormattedOutput * output,
                                             unsigned num )
{
  if( output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  switch( output->format ){
    case STUMPLESS_TEXT:
      return StumplessAppendUnsignedIntToValueList( output->payload->values,
                                                    num );
    default:
      return STUMPLESS_FAILURE;
  }
}

StumplessStatusCode
StumplessAppendValueToFormattedOutput( StumplessFormattedOutput * output,
                                       StumplessValue * value )
{
  if( output == NULL || value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  switch( output->format ){
    case STUMPLESS_TEXT:
      return StumplessAppendValueToValueList( output->payload->values, value );
    default:
      return STUMPLESS_FAILURE;
  }
}

StumplessStatusCode
StumplessFormattedOutputIntoString( char * str,
                                    StumplessFormattedOutput * output )
{
  if( str == NULL || output == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  switch( output->format ){
    case STUMPLESS_TEXT:
      return StumplessValueListIntoString( str, output->payload->values );
    default:
      return STUMPLESS_FAILURE;
  }
}

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * output )
{
  if( output == NULL || output->payload == NULL )
    return 1;
  
  switch( output->format ){
    case STUMPLESS_TEXT:
      return StumplessValueListIsEmpty( output->payload->values );
  }
  return 0;
}

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * output )
{
  if( output == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
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
