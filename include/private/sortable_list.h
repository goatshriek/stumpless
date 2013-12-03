#ifndef __STUMPLESS_PRIVATE_SORTABLE_LIST_H
#define __STUMPLESS_PRIVATE_SORTABLE_LIST_H

#include "private/type.h"

SortableList *
AppendSortableLists
( SortableList *, SortableList * );

SortableList *
AppendToSortableList
( SortableList *, void * );

void *
BeginSortableList
( SortableList * );

SortableList *
CopySortableList
( SortableList * );

void
DestroySortableList
( SortableList * );

unsigned short
SortableListContains
( SortableList *, void * );

unsigned short
SortableListIsEmpty
( SortableList * );

void *
NextInSortableList
( SortableList * );

SortableList *
NewSortableList
();

SortableList *
PrependToSortableList
( SortableList *, void * );

SortableList *
SetSortableListComparison
( SortableList *, unsigned short ( *compare )( void *, void *, Dictionary * ) );

#endif
