#ifndef __STUMPLESS_LIST_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_LIST_ITERATOR_EVENT_ATTRIBUTE_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( EventAttributeListIteratorHasNext )
( const __STUMPLESS_NAME( EventAttributeListIterator ) * );

__STUMPLESS_NAME( EventAttributeListIterator ) *
__STUMPLESS_NAME( CopyEventAttributeListIterator )
( const __STUMPLESS_NAME( EventAttributeListIterator ) * );

void
__STUMPLESS_NAME( DestroyEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeListIterator ) * );

__STUMPLESS_NAME( EventAttributeListIterator ) *
__STUMPLESS_NAME( NewEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeList ) * );

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( NextInEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeListIterator ) * );

#endif
