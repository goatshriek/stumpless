#ifndef __STUMPLESS_PRIVATE_COMPARATOR_H
#define __STUMPLESS_PRIVATE_COMPARATOR_H

#include "private/type.h"

Exception *
AddComparator
( Comparator * );

void
DestroyComparator
( Comparator * );

Comparator *
FindComparatorByName
( const char * );

void *
GetComparatorOption
( const Comparator *, const char * );

Exception *
SetComparatorOption
( Comparator *, const char *, void * );

#endif
