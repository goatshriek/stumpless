#ifndef __STUMPLESS_LIST_ITERATOR_VALUE_H
#define __STUMPLESS_LIST_ITERATOR_VALUE_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( ValueListIteratorHasNext )
( const __STUMPLESS_NAME( ValueListIterator ) * );

__STUMPLESS_NAME( ValueListIterator ) *
__STUMPLESS_NAME( CopyValueListIterator )
( const __STUMPLESS_NAME( ValueListIterator ) * );

void
__STUMPLESS_NAME( DestroyValueListIterator )
( __STUMPLESS_NAME( ValueListIterator ) * );

__STUMPLESS_NAME( ValueListIterator ) *
__STUMPLESS_NAME( NewValueListIterator )
( __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( NextInValueListIterator )
( __STUMPLESS_NAME( ValueListIterator ) * );

#endif
