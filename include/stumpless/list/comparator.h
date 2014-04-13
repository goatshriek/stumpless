#ifndef __STUMPLESS_LIST_COMPARATOR_LIST_H
#define __STUMPLESS_LIST_COMPARATOR_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AddSeparatorToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) *, __STUMPLESS_NAME( Comparator ) * );

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AppendComparatorLists )
( __STUMPLESS_NAME( ComparatorList ) *, __STUMPLESS_NAME( ComparatorList ) * );

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AppendToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) *, __STUMPLESS_NAME( Comparator ) * );

unsigned short
__STUMPLESS_NAME( ComparatorListContains )
( __STUMPLESS_NAME( ComparatorList ) *, __STUMPLESS_NAME( Comparator ) * );

unsigned short
__STUMPLESS_NAME( ComparatorListIsEmpty )
( __STUMPLESS_NAME( ComparatorList ) * );

unsigned
__STUMPLESS_NAME( ComparatorListSize )
( const __STUMPLESS_NAME( ComparatorList ) * );

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( CopyComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * );

void
__STUMPLESS_NAME( DestroyComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * );

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( NewComparatorList )
( void );

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( PrependToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) *, __STUMPLESS_NAME( Comparator ) * );

short
__STUMPLESS_NAME( RunComparatorList )
( __STUMPLESS_NAME( ComparatorList ) *, const void *, const void * );

#endif
