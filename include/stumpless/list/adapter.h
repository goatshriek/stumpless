#ifndef __STUMPLESS_LIST_ADAPTER_LIST_H
#define __STUMPLESS_LIST_ADAPTER_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( AdapterListContains )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

unsigned short
__STUMPLESS_NAME( AdapterListIsEmpty )
( __STUMPLESS_NAME( AdapterList ) * );

unsigned
__STUMPLESS_NAME( AdapterListSize )
( const __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AddSeparatorToAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AppendAdapterLists )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( AppendToAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( CopyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

void
__STUMPLESS_NAME( DestroyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( NewAdapterList )
( void );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( PrependToAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( ValueThroughAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Value ) * );

#endif
