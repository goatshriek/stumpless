#include <stdlib.h>

#include "private/sortable_list.h"
#include "private/sortable_list_static.h"
#include "private/type.h"

SortableList *
AddToSortableList
( SortableList * list, void * value )
{
  return NULL;
}

void *
BeginSortableList
( SortableList * list )
{
  return NULL;
}

SortableList *
CopySortableList
( SortableList * list )
{
  return NULL;
}

void
DestroySortableList
( SortableList * list )
{
  return;
}

SortableList *
MergeSortableLists
( SortableList * first, SortableList * second )
{
  return NULL;
}

void *
NextInSortableList
( SortableList * list )
{
  return NULL;
}

SortableList *
NewSortableList
()
{
  return NULL;
}

SortableList *
NewSortableListFromList
( List * list, unsigned short ( *compare )( const void *, const void *, Dictionary * ) )
{
  return NULL;
}

SortableList *
SetSortableListComparison
( SortableList * list, unsigned short ( *compare )( const void *, const void *, Dictionary * ) )
{
  return NULL;
}

SortableList *
SetSortableListOptions
( SortableList * list, Dictionary * options )
{
  return NULL;
}

unsigned short
SortableListContains
( SortableList * list, void * value )
{
  return 0;
}

unsigned short
SortableListIsEmpty
( SortableList * list )
{
  return 0;
}

static
void
DestroyNode
( Node * node )
{
  return;
}
