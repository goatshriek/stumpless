#ifndef __STUMPLESS_PRIVATE_SORTABLE_LIST_H
#define __STUMPLESS_PRIVATE_SORTABLE_LIST_H

#include "private/type.h"

SortableList *
AddToSortableList
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

SortableList *
MergeSortableLists
( SortableList *, SortableList * );

void *
NextInSortableList
( SortableList * );

SortableList *
NewSortableList
();

SortableList *
NewSortableListFromList
( List *, short ( *compare )( const void *, const void *, Dictionary * ) );

SortableList *
SetSortableListComparison
( SortableList *, short ( *compare )( const void *, const void *, Dictionary * ) );

SortableList *
SetSortableListOptions
( SortableList *, Dictionary * );

unsigned short
SortableListContains
( SortableList *, void * );

unsigned short
SortableListIsEmpty
( SortableList * );

#endif
