#ifndef STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_LIST_H
#define STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_LIST_H

#include "private/type.h"

Status *
AppendToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

EntryAttribute *
BeginEntryAttributeList
( EntryAttributeList * );

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
NewEntryAttributeList
( void );

EntryAttribute *
NextInEntryAttributeList
( EntryAttributeList * );

Status *
PrependToEntryAttributeList
( EntryAttributeList *, EntryAttribute * );

#endif
