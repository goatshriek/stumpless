#include "stumpless/list/iterator/entry_attribute.h"

#include "private/list/iterator/entry_attribute.h"

unsigned short
__STUMPLESS_NAME( EntryAttributeListIteratorHasNext )
( const __STUMPLESS_NAME( EntryAttributeListIterator ) * iterator )
{
  return EntryAttributeListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( EntryAttributeListIterator ) *
__STUMPLESS_NAME( CopyEntryAttributeListIterator )
( const __STUMPLESS_NAME( EntryAttributeListIterator ) * iterator )
{
  return CopyEntryAttributeListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeListIterator ) * iterator )
{
  DestroyEntryAttributeListIterator( iterator );
  return;
}

__STUMPLESS_NAME( EntryAttributeListIterator ) *
__STUMPLESS_NAME( NewEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return NewEntryAttributeListIterator( list );
}

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( NextInEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeListIterator ) * iterator )
{
  return NextInEntryAttributeListIterator( iterator );
}
