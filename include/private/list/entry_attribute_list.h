#ifndef STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_LIST_H
#define STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_LIST_H

#include "private/type.h"

Status *
AppendToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttributeList *
CopyEntryAttributeList
( EntryAttributeList * );

void
DestroyEntryAttributeList
( EntryAttributeList * );

unsigned short
EntryAttributeListIsEmpty
( EntryAttributeList * );

EntryAttributeList *
MergeEntryAttributeLists
( EntryAttributeList *, EntryAttributeList * );

EntryAttributeList *
NewEntryAttributeList
( void );

Status *
PrependToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

#endif
