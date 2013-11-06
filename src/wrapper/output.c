#include "stumpless/output.h"

#include "private/output.h"

unsigned short
__STUMPLESS_NAME( BinaryOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return BinaryOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( BinaryOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return BinaryOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( CSVOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return CSVOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( CSVOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return CSVOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( OutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return OutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( OutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return OutputToString( output );
}

unsigned short
__STUMPLESS_NAME( JSONOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return JSONOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( JSONOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return JSONOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( RawStringOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return RawStringOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( RawStringOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return RawStringOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( TextOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return TextOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( TextOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return TextOutputToString( output );
}

unsigned short
__STUMPLESS_NAME( XMLOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * output )
{
  return XMLOutputIsEmpty( output );
}

char *
__STUMPLESS_NAME( XMLOutputToString )
( __STUMPLESS_NAME( Output ) * output )
{
  return XMLOutputToString( output );
}
