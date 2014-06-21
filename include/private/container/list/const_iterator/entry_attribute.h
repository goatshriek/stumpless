#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_ENTRY_ATTRIBUTE_H

#include "private/type.h"

EntryAttributeListConstIterator *
CopyEntryAttributeListConstIterator
( const EntryAttributeListConstIterator * );

void
DestroyEntryAttributeListConstIterator
( EntryAttributeListConstIterator * );

unsigned short
EntryAttributeListConstIteratorHasNext
( const EntryAttributeListConstIterator * );

EntryAttributeListConstIterator *
NewEntryAttributeListConstIterator
( const EntryAttributeList *, int );

const EntryAttribute *
NextInEntryAttributeListConstIterator
( EntryAttributeListConstIterator * );

#endif
