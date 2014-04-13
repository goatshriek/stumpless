#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_ENTRY_ATTRIBUTE_H

#include "private/type.h"

EntryAttributeListReverseIterator *
CopyEntryAttributeListReverseIterator
( const EntryAttributeListReverseIterator * );

void
DestroyEntryAttributeListReverseIterator
( EntryAttributeListReverseIterator * );

unsigned short
EntryAttributeListReverseIteratorHasNext
( const EntryAttributeListReverseIterator * );

EntryAttributeListReverseIterator *
NewEntryAttributeListReverseIterator
( EntryAttributeList *, int );

EntryAttribute *
NextInEntryAttributeListReverseIterator
( EntryAttributeListReverseIterator * );

#endif
