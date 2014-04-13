#include "stumpless/list/iterator/event_attribute.h"

#include "private/list/iterator/event_attribute.h"

unsigned short
__STUMPLESS_NAME( EventAttributeListIteratorHasNext )
( const __STUMPLESS_NAME( EventAttributeListIterator ) * iterator )
{
  return EventAttributeListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( EventAttributeListIterator ) *
__STUMPLESS_NAME( CopyEventAttributeListIterator )
( const __STUMPLESS_NAME( EventAttributeListIterator ) * iterator )
{
  return CopyEventAttributeListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeListIterator ) * iterator )
{
  DestroyEventAttributeListIterator( iterator );
  return;
}

__STUMPLESS_NAME( EventAttributeListIterator ) *
__STUMPLESS_NAME( NewEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return NewEventAttributeListIterator( list );
}

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( NextInEventAttributeListIterator )
( __STUMPLESS_NAME( EventAttributeListIterator ) * iterator )
{
  return NextInEventAttributeListIterator( iterator );
}
