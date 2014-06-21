#ifndef __STUMPLESS_LIST_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_LIST_ITERATOR_ENTRY_ATTRIBUTE_H

#include <stumpless/type.h>

unsigned short
EntryAttributeListIteratorHasNext
( const EntryAttributeListIterator * );

EntryAttributeListIterator *
CopyEntryAttributeListIterator
( const EntryAttributeListIterator * );

void
DestroyEntryAttributeListIterator
( EntryAttributeListIterator * );

EntryAttributeListIterator *
NewEntryAttributeListIterator
( EntryAttributeList * );

EntryAttribute *
NextInEntryAttributeListIterator
( EntryAttributeListIterator * );

#endif
