#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_ENTRY_ATTRIBUTE_H

#include "private/type.h"

EntryAttributeListIterator *
CopyEntryAttributeListIterator
( const EntryAttributeListIterator * );

void
DestroyEntryAttributeListIterator
( EntryAttributeListIterator * );

unsigned short
EntryAttributeListIteratorHasNext
( const EntryAttributeListIterator * );

EntryAttributeListIterator *
NewEntryAttributeListIterator
( EntryAttributeList *, int );

EntryAttribute *
NextInEntryAttributeListIterator
( EntryAttributeListIterator * );

#endif
