#ifndef __STUMPLESS_PRIVATE_LIST_FILTER_H
#define __STUMPLESS_PRIVATE_LIST_FILTER_H

#include "private/type.h"

FilterList *
AddSeparatorToFilterList
( FilterList *, Filter * );

FilterList *
AppendFilterLists
( FilterList *, FilterList * );

FilterList *
AppendToFilterList
( FilterList *, Filter * );

FilterListIterator *
BeginFilterList
( FilterList * );

FilterListConstIterator *
CBeginFilterList
( const FilterList * );

FilterListConstIterator *
CEndFilterList
( const FilterList * );

FilterList *
CopyFilterList
( const FilterList * );

FilterListConstReverseIterator *
CRBeginFilterList
( const FilterList * );

FilterListConstReverseIterator *
CREndFilterList
( const FilterList * );

void
DestroyFilterList
( FilterList * );

FilterListIterator *
EndFilterList
( FilterList * );

unsigned short
EntryThroughFilterList
( const FilterList *, const Entry * );

unsigned short
FilterListContains
( const FilterList *, const Filter * );

unsigned short
FilterListIsEmpty
( const FilterList * );

unsigned
FilterListSize
( const FilterList * );

FilterList *
NewFilterList
( void );

unsigned short
OutputThroughFilterList
( const FilterList *, const Output * );

FilterList *
PrependToFilterList
( FilterList *, Filter * );

FilterListReverseIterator *
RBeginFilterList
( FilterList * );

FilterListReverseIterator *
REndFilterList
( FilterList * );

unsigned short
ValueThroughFilterList
( const FilterList *, const Value * );

#endif
