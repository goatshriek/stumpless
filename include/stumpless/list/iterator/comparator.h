#ifndef __STUMPLESS_LIST_ITERATOR_COMPARATOR_H
#define __STUMPLESS_LIST_ITERATOR_COMPARATOR_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( ComparatorListIteratorHasNext )
( const __STUMPLESS_NAME( ComparatorListIterator ) * );

__STUMPLESS_NAME( ComparatorListIterator ) *
__STUMPLESS_NAME( CopyComparatorListIterator )
( const __STUMPLESS_NAME( ComparatorListIterator ) * );

void
__STUMPLESS_NAME( DestroyComparatorListIterator )
( __STUMPLESS_NAME( ComparatorListIterator ) * );

__STUMPLESS_NAME( ComparatorListIterator ) *
__STUMPLESS_NAME( NewComparatorListIterator )
( __STUMPLESS_NAME( ComparatorList ) * );

__STUMPLESS_NAME( Comparator ) *
__STUMPLESS_NAME( NextInComparatorListIterator )
( __STUMPLESS_NAME( ComparatorListIterator ) * );

#endif
