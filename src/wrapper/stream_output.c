#include <stream_output.h>

#include "private/stream_output.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BinaryFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return BinaryFormattedOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CSVFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return CSVFormattedOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( JSONFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return JSONFormattedOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( RawStringFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return RawStringFormattedOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( TextFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return TextFormattedOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( XMLFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) * output, FILE * stream )
{
  return XMLFormattedOutputIntoStream( output, stream );
}
