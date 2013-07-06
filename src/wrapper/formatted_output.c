#include <formatted_output.h>

#include "private/formatted_output.h"

unsigned short
__STUMPLESS_NAME( BinaryFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return BinaryFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( BinaryFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return BinaryFormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( CSVFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return CSVFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( CSVFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return CSVFormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( FormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return FormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( FormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return FormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( JSONFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return JSONFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( JSONFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return JSONFormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( RawStringFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return RawStringFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( RawStringFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output );
{
  return RawStringFormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( TextFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return TextFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( TextFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return TextFormattedOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( XMLFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return XMLFormattedOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( XMLFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * output )
{
  return XMLFormattedOutputToString( output );
}
