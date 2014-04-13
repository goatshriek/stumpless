#include "stumpless/list/iterator/comparator.h"

#include "private/list/iterator/comparator.h"

unsigned short
__STUMPLESS_NAME( ComparatorListIteratorHasNext )
( const __STUMPLESS_NAME( ComparatorListIterator ) * iterator )
{
  return ComparatorListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( ComparatorListIterator ) *
__STUMPLESS_NAME( CopyComparatorListIterator )
( const __STUMPLESS_NAME( ComparatorListIterator ) * iterator )
{
  return CopyComparatorListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyComparatorListIterator )
( __STUMPLESS_NAME( ComparatorListIterator ) * iterator )
{
  DestroyComparatorListIterator( iterator );
  return;
}

__STUMPLESS_NAME( ComparatorListIterator ) *
__STUMPLESS_NAME( NewComparatorListIterator )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return NewComparatorListIterator( list );
}

__STUMPLESS_NAME( Comparator ) *
__STUMPLESS_NAME( NextInComparatorListIterator )
( __STUMPLESS_NAME( ComparatorListIterator ) * iterator )
{
  return NextInComparatorListIterator( iterator );
}
