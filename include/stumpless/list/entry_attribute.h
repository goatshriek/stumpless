#ifndef __STUMPLESS_LIST_ENTRY_ATTRIBUTE_LIST_H
#define __STUMPLESS_LIST_ENTRY_ATTRIBUTE_LIST_H

#include <stumpless/type.h>

EntryAttributeList *
AddSeparatorToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeList *
AppendEntryAttributeLists
( EntryAttributeList *, EntryAttributeList * );

EntryAttributeList *
AppendToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeList *
CopyEntryAttributeList
( EntryAttributeList * );

void
DestroyEntryAttributeList
( EntryAttributeList * );

unsigned short
EntryAttributeListContains
( EntryAttributeList *, EntryAttribute * );

unsigned short
EntryAttributeListIsEmpty
( EntryAttributeList * );

unsigned
EntryAttributeListSize
( const EntryAttributeList * );

EntryAttributeList *
MergeEntryAttributeLists
( EntryAttributeList *, EntryAttributeList * );

EntryAttributeList *
NewEntryAttributeList
( void );

EntryAttributeList *
PrependToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

#endif
