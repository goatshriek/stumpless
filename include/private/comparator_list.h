#ifndef STUMPLESS_PRIVATE_COMPARATOR_LIST_H
#define STUMPLESS_PRIVATE_COMPARATOR_LIST_H

#include "private/type.h"

Status *
AppendToComparatorList
( ComparatorList *, Comparator * );

Comparator *
BeginComparatorList
( ComparatorList * );

unsigned short
ComparatorListIsEmpty
( ComparatorList * );

ComparatorList *
CopyComparatorList
( ComparatorList * );

void
DestroyComparatorList
( ComparatorList * );

ComparatorList *
NewComparatorList
( void );

Comparator *
NextInComparatorList
( ComparatorList * );

Status *
PrependToComparatorList
( ComparatorList *, Comparator * );

short
RunComparatorList
( ComparatorList *, const void *, const void * );

#endif
