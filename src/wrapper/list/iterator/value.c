#include "stumpless/list/iterator/value.h"

#include "private/list/iterator/value.h"

unsigned short
__STUMPLESS_NAME( ValueListIteratorHasNext )
( const __STUMPLESS_NAME( ValueListIterator ) * iterator )
{
  return ValueListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( ValueListIterator ) *
__STUMPLESS_NAME( CopyValueListIterator )
( const __STUMPLESS_NAME( ValueListIterator ) * iterator )
{
  return CopyValueListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyValueListIterator )
( __STUMPLESS_NAME( ValueListIterator ) * iterator )
{
  DestroyValueListIterator( iterator );
  return;
}

__STUMPLESS_NAME( ValueListIterator ) *
__STUMPLESS_NAME( NewValueListIterator )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return NewValueListIterator( list );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( NextInValueListIterator )
( __STUMPLESS_NAME( ValueListIterator ) * iterator )
{
  return NextInValueListIterator( iterator );
}
