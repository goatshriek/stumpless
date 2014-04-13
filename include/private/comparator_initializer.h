#ifndef STUMPLESS_PRIVATE_COMPARATOR_INITIALIZER_H
#define STUMPLESS_PRIVATE_COMPARATOR_INITIALIZER_H

#include "private/type.h"

Status *
InitializeComparatorByName
( const char * );

Comparator *
InitializeStringComparator
( void );

#endif
