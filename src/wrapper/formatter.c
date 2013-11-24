#include "stumpless/formatter.h"

#include "private/formatter.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFormatter )
( __STUMPLESS_NAME( Formatter ) * formatter )
{
  return AddFormatter( formatter );
}

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( FindFormatterByName )
( const char * name )
{
  return FindFormatterByName( name );
}

void *
__STUMPLESS_NAME( GetFormatterOption )
( const __STUMPLESS_NAME( Formatter ) * formatter, const char * option )
{
  return GetFormatterOption( formatter, option );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetFormatterOption )
( __STUMPLESS_NAME( Formatter ) * formatter, const char * option, void * value )
{
  return SetFormatterOption( formatter, option, value );
}
