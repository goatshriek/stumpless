#ifndef __STUMPLESS_LIST_ITERATOR_FILTER_H
#define __STUMPLESS_LIST_ITERATOR_FILTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( FilterListIteratorHasNext )
( const __STUMPLESS_NAME( FilterListIterator ) * );

__STUMPLESS_NAME( FilterListIterator ) *
__STUMPLESS_NAME( CopyFilterListIterator )
( const __STUMPLESS_NAME( FilterListIterator ) * );

void
__STUMPLESS_NAME( DestroyFilterListIterator )
( __STUMPLESS_NAME( FilterListIterator ) * );

__STUMPLESS_NAME( FilterListIterator ) *
__STUMPLESS_NAME( NewFilterListIterator )
( __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( NextInFilterListIterator )
( __STUMPLESS_NAME( FilterListIterator ) * );

#endif
