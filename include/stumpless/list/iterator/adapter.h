#ifndef __STUMPLESS_LIST_ITERATOR_ADAPTER_H
#define __STUMPLESS_LIST_ITERATOR_ADAPTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( AdapterListIteratorHasNext )
( const __STUMPLESS_NAME( AdapterListIterator ) * );

__STUMPLESS_NAME( AdapterListIterator ) *
__STUMPLESS_NAME( CopyAdapterListIterator )
( const __STUMPLESS_NAME( AdapterListIterator ) * );

void
__STUMPLESS_NAME( DestroyAdapterListIterator )
( __STUMPLESS_NAME( AdapterListIterator ) * );

__STUMPLESS_NAME( AdapterListIterator ) *
__STUMPLESS_NAME( NewAdapterListIterator )
( __STUMPLESS_NAME( AdapterList ) * );

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( NextInAdapterListIterator )
( __STUMPLESS_NAME( AdapterListIterator ) * );

#endif
