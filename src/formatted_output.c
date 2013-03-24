#include <formatted_output.h>
#include <types.h>

StumplessStatusCode
StumplessAppendFormattedOutput( StumplessFormattedOutput * beginning,
                                StumplessFormattedOutput * end )
{
  if( beginning == NULL || end == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( beginning->format != end->format )
    return STUMPLESS_INCOMPATIBLE_ARGUMENTS;
  
  switch( beginning->format ){
    case STUMPLESS_TEXT:
      return StumplessAppendValueListToValueList( beginning->payload->values,
                                                  end->payload->values );
    default:
      return STUMPLESS_FAILURE;
  }
}
