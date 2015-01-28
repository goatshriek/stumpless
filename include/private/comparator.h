#ifndef __STUMPLESS_PRIVATE_COMPARATOR_H
#define __STUMPLESS_PRIVATE_COMPARATOR_H

#include "private/type.h"

Comparator *
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

Comparator *
SetComparatorOption
( Comparator *, const char *, void * );

#endif
