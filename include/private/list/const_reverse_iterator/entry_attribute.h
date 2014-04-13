#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_ENTRY_ATTRIBUTE_H

#include "private/type.h"

EntryAttributeListConstReverseIterator *
CopyEntryAttributeListConstReverseIterator
( const EntryAttributeListConstReverseIterator * );

void
DestroyEntryAttributeListConstReverseIterator
( EntryAttributeListConstReverseIterator * );

unsigned short
EntryAttributeListConstReverseIteratorHasNext
( const EntryAttributeListConstReverseIterator * );

EntryAttributeListConstReverseIterator *
NewEntryAttributeListConstReverseIterator
( const EntryAttributeList *, int );

const EntryAttribute *
NextInEntryAttributeListConstReverseIterator
( EntryAttributeListConstReverseIterator * );

#endif
