#ifndef __STUMPLESS_ADAPTER_LIST_H
#define __STUMPLESS_ADAPTER_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( BeginAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( CopyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

void
__STUMPLESS_NAME( DestroyAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

unsigned short
__STUMPLESS_NAME( AdapterListIsEmpty )
( __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( AdapterList ) *
__STUMPLESS_NAME( NewAdapterList )
( void );

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( NextInAdapterList )
( __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( ValueThroughAdapterList )
( __STUMPLESS_NAME( AdapterList ) *, __STUMPLESS_NAME( Value ) * );

#endif
