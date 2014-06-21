#ifndef __STUMPLESS_PRIVATE_LIST_COMPARATOR_H
#define __STUMPLESS_PRIVATE_LIST_COMPARATOR_H

#include "private/type.h"

ComparatorList *
AddSeparatorToComparatorList
( ComparatorList *, Comparator * );

ComparatorList *
AppendComparatorLists
( ComparatorList *, ComparatorList * );

ComparatorList *
AppendToComparatorList
( ComparatorList *, Comparator * );

ComparatorListIterator *
BeginComparatorList
( ComparatorList * );

ComparatorListConstIterator *
CBeginComparatorList
( const ComparatorList * );

ComparatorListConstIterator *
CEndComparatorList
( const ComparatorList * );

Comparator *
ComparatorListBack
( const ComparatorList * );

unsigned short
ComparatorListContains
( const ComparatorList *, const Comparator * );

Comparator *
ComparatorListFront
( const ComparatorList * );

unsigned short
ComparatorListIsEmpty
( const ComparatorList * );

unsigned
ComparatorListSize
( const ComparatorList * );

ComparatorList *
CopyComparatorList
( const ComparatorList * );

ComparatorListConstReverseIterator *
CRBeginComparatorList
( const ComparatorList * );

ComparatorListConstReverseIterator *
CREndComparatorList
( const ComparatorList * );

void
DestroyComparatorList
( ComparatorList * );

ComparatorListIterator *
EndComparatorList
( ComparatorList * );

ComparatorList *
NewComparatorList
();

ComparatorList *
PrependToComparatorList
( ComparatorList *, Comparator * );

ComparatorListReverseIterator *
RBeginComparatorList
( ComparatorList * );

ComparatorListReverseIterator *
REndComparatorList
( ComparatorList * );

short
RunComparatorList
( ComparatorList *, const void *, const void * );

#endif
