#include "stumpless/adapter.h"

#include "private/adapter.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddAdapter )
( __STUMPLESS_NAME( Adapter ) * adapter )
{
  return AddAdapter( adapter );
}

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( FindAdapterByName )
( const char * name )
{
  return FindAdapterByName( name );
}

void *
__STUMPLESS_NAME( GetAdapterOption )
( const __STUMPLESS_NAME( Adapter ) * adapter, const char * option )
{
  return GetAdapterOption( adapter, option );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetAdapterOption )
( __STUMPLESS_NAME( Adapter ) * adapter, const char * option, void * value )
{
  return SetAdapterOption( adapter, option, value );
}
