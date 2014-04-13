#include "stumpless/list/iterator/filter.h"

#include "private/list/iterator/filter.h"

unsigned short
__STUMPLESS_NAME( FilterListIteratorHasNext )
( const __STUMPLESS_NAME( FilterListIterator ) * iterator )
{
  return FilterListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( FilterListIterator ) *
__STUMPLESS_NAME( CopyFilterListIterator )
( const __STUMPLESS_NAME( FilterListIterator ) * iterator )
{
  return CopyFilterListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyFilterListIterator )
( __STUMPLESS_NAME( FilterListIterator ) * iterator )
{
  DestroyFilterListIterator( iterator );
  return;
}

__STUMPLESS_NAME( FilterListIterator ) *
__STUMPLESS_NAME( NewFilterListIterator )
( __STUMPLESS_NAME( FilterList ) * list )
{
  return NewFilterListIterator( list );
}

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( NextInFilterListIterator )
( __STUMPLESS_NAME( FilterListIterator ) * iterator )
{
  return NextInFilterListIterator( iterator );
}
