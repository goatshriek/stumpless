#include "stumpless/list/adapter.h"

#include "private/list/adapter.h"

unsigned short
__STUMPLESS_NAME( AdapterListContains )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Adapter ) * adapter )
{
  return AdapterListContains( list, adapter );
}

unsigned short
__STUMPLESS_NAME( AdapterListIsEmpty )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return AdapterListIsEmpty( list );
}

unsigned
__STUMPLESS_NAME( AdapterListSize )
( const __STUMPLESS_NAME( AdapterList ) * list )
{
  return AdapterListSize( list );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AddSeparatorToAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Adapter ) * separator )
{
  return AddSeparatorToAdapterList( list, separator );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AppendAdapterLists )
( __STUMPLESS_NAME( AdapterList ) * first, __STUMPLESS_NAME( AdapterList ) * second )
{
  return AppendAdapterLists( first, second );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AppendToAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Adapter ) * adapter )
{
  return AppendToAdapterList( list, adapter );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( CopyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return CopyAdapterList( list );
}

void
__STUMPLESS_NAME( DestroyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  DestroyAdapterList( list );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( NewAdapterList )
( void )
{
  return NewAdapterList();
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( PrependToAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Adapter ) * adapter )
{
  return PrependToAdapterList( list, adapter );
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( ValueThroughAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Value ) * value )
{
  return ValueThroughAdapterList( list, value );
}
