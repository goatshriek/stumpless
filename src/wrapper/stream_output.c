#include <stream_output.h>

#include "private/stream_output.h"

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( TextOutputToStream )
( FILE * stream, __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return TextOutputToStream( stream, output );
}
