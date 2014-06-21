#ifndef __STUMPLESS_LIST_FILTER_LIST_H
#define __STUMPLESS_LIST_FILTER_LIST_H

#include <stumpless/type.h>

FilterList *
AddSeparatorToFilterList
( FilterList *, Filter * );

FilterList *
AppendFilterLists
( FilterList *, FilterList * );

FilterList *
AppendToFilterList
( FilterList *, Filter * );

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
FilterListContains
( FilterList *, Filter * );

unsigned short
FilterListIsEmpty
( FilterList * );

unsigned
FilterListSize
( const FilterList * );

FilterList *
NewFilterList
( void );

unsigned short
OutputThroughFilterList
( FilterList *, Output * );

FilterList *
PrependToFilterList
( FilterList *, Filter * );

unsigned short
ValueThroughFilterList
( FilterList *, Value * );

#endif
