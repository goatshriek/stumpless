#ifndef __STUMPLESS_PRIVATE_LIST_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_ENTRY_ATTRIBUTE_H

#include "private/type.h"

EntryAttributeList *
AddSeparatorToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeList *
AppendEntryAttributeLists
( EntryAttributeList *, EntryAttributeList * );

EntryAttributeList *
AppendToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeListIterator *
BeginEntryAttributeList
( EntryAttributeList * );

EntryAttributeListConstIterator *
CBeginEntryAttributeList
( const EntryAttributeList * );

EntryAttributeListConstIterator *
CEndEntryAttributeList
( const EntryAttributeList * );

EntryAttributeList *
CopyEntryAttributeList
( const EntryAttributeList * );

EntryAttributeListConstReverseIterator *
CRBeginEntryAttributeList
( const EntryAttributeList * );

EntryAttributeListConstReverseIterator *
CREndEntryAttributeList
( const EntryAttributeList * );

void
DestroyEntryAttributeList
( EntryAttributeList * );

EntryAttributeListIterator *
EndEntryAttributeListIterator
( EntryAttributeList * );

unsigned short
EntryAttributeListContains
( const EntryAttributeList *, const EntryAttribute * );

unsigned short
EntryAttributeListIsEmpty
( const EntryAttributeList * );

unsigned
EntryAttributeListSize
( const EntryAttributeList * );

EntryAttributeList *
MergeEntryAttributeLists
( EntryAttributeList *, EntryAttributeList * );

EntryAttributeList *
NewEntryAttributeList
();

EntryAttributeList *
PrependToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeListReverseIterator *
RBeginEntryAttributeList
( EntryAttributeList * );

EntryAttributeListReverseIterator *
REndEntryAttributeList
( EntryAttributeList * );

#endif
