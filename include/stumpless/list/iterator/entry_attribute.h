#ifndef __STUMPLESS_LIST_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_LIST_ITERATOR_ENTRY_ATTRIBUTE_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( EntryAttributeListIteratorHasNext )
( const __STUMPLESS_NAME( EntryAttributeListIterator ) * );

__STUMPLESS_NAME( EntryAttributeListIterator ) *
__STUMPLESS_NAME( CopyEntryAttributeListIterator )
( const __STUMPLESS_NAME( EntryAttributeListIterator ) * );

void
__STUMPLESS_NAME( DestroyEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeListIterator ) * );

__STUMPLESS_NAME( EntryAttributeListIterator ) *
__STUMPLESS_NAME( NewEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeList ) * );

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( NextInEntryAttributeListIterator )
( __STUMPLESS_NAME( EntryAttributeListIterator ) * );

#endif
