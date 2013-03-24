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
