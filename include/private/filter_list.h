#ifndef STUMPLESS_PRIVATE_FILTER_LIST_H
#define STUMPLESS_PRIVATE_FILTER_LIST_H

#include <stdio.h>

#include "private/type.h"

Status *
AppendToFilterList
( FilterList *, Filter * );

Filter *
BeginFilterList
( FilterList * );

FilterList *
CopyFilterList
( FilterList * );

void
DestroyFilterList
( FilterList * );

unsigned short
EntryThroughFilterList
( FilterList *, Entry * );

unsigned short
FilterListIsEmpty
( FilterList * );

FilterList *
NewFilterList
( void );

Filter *
NextInFilterList
( FilterList * );

unsigned short
OutputThroughFilterList
( FilterList *, Output * );

Status *
PrependToFilterList
( FilterList *, Filter * );

unsigned short
ValueThroughFilterList
( FilterList *, Value * );

#endif
