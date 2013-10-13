#include <stream_output.h>

#include "private/stream_output.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BinaryOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return BinaryOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CSVOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return CSVOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( JSONOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return JSONOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( RawStringOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return RawStringOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( TextOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return TextOutputIntoStream( output, stream );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( XMLOutputIntoStream )
( __STUMPLESS_NAME( Output ) * output, FILE * stream )
{
  return XMLOutputIntoStream( output, stream );
}
