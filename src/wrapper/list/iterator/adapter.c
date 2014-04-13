#include "stumpless/list/iterator/adapter.h"

#include "private/list/iterator/adapter.h"

unsigned short
__STUMPLESS_NAME( AdapterListIteratorHasNext )
( const __STUMPLESS_NAME( AdapterListIterator ) * iterator )
{
  return AdapterListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( AdapterListIterator ) *
__STUMPLESS_NAME( CopyAdapterListIterator )
( const __STUMPLESS_NAME( AdapterListIterator ) * iterator )
{
  return CopyAdapterListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyAdapterListIterator )
( __STUMPLESS_NAME( AdapterListIterator ) * iterator )
{
  DestroyAdapterListIterator( iterator );
  return;
}

__STUMPLESS_NAME( AdapterListIterator ) *
__STUMPLESS_NAME( NewAdapterListIterator )
( __STUMPLESS_NAME( AdapterList ) * list )
{
  return NewAdapterListIterator( list );
}

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( NextInAdapterListIterator )
( __STUMPLESS_NAME( AdapterListIterator ) * iterator )
{
  return NextInAdapterListIterator( iterator );
}
