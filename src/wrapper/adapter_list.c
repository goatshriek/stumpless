#include "stumpless/adapter_list.h"

#include "private/adapter_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list, __STUMPLESS_NAME( Adapter ) * adapter )
{
  return AppendToAdapterList( list, adapter );
}

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( BeginAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return BeginAdapterList( list );
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

unsigned short
__STUMPLESS_NAME( AdapterListIsEmpty )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return AdapterListIsEmpty( list );
}

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( NewAdapterList )
( void )
{
  return NewAdapterList();
}

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( NextInAdapterList )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return NextInAdapterList( list );
}

__STUMPLESS_NAME( Status ) *
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
