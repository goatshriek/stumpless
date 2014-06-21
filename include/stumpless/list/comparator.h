#ifndef __STUMPLESS_LIST_COMPARATOR_LIST_H
#define __STUMPLESS_LIST_COMPARATOR_LIST_H

#include <stumpless/type.h>

ComparatorList *
AddSeparatorToComparatorList
( ComparatorList *, Comparator * );

ComparatorList *
AppendComparatorLists
( ComparatorList *, ComparatorList * );

ComparatorList *
AppendToComparatorList
( ComparatorList *, Comparator * );

unsigned short
ComparatorListContains
( ComparatorList *, Comparator * );

unsigned short
ComparatorListIsEmpty
( ComparatorList * );

unsigned
ComparatorListSize
( const ComparatorList * );

ComparatorList *
CopyComparatorList
( ComparatorList * );

void
DestroyComparatorList
( ComparatorList * );

ComparatorList *
NewComparatorList
( void );

ComparatorList *
PrependToComparatorList
( ComparatorList *, Comparator * );

short
RunComparatorList
( ComparatorList *, const void *, const void * );

#endif
