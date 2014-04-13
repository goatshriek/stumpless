#include "stumpless/list/iterator/formatter.h"

#include "private/list/iterator/formatter.h"

unsigned short
__STUMPLESS_NAME( FormatterListIteratorHasNext )
( const __STUMPLESS_NAME( FormatterListIterator ) * iterator )
{
  return FormatterListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( FormatterListIterator ) *
__STUMPLESS_NAME( CopyFormatterListIterator )
( const __STUMPLESS_NAME( FormatterListIterator ) * iterator )
{
  return CopyFormatterListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyFormatterListIterator )
( __STUMPLESS_NAME( FormatterListIterator ) * iterator )
{
  DestroyFormatterListIterator( iterator );
  return;
}

__STUMPLESS_NAME( FormatterListIterator ) *
__STUMPLESS_NAME( NewFormatterListIterator )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  return NewFormatterListIterator( list );
}

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( NextInFormatterListIterator )
( __STUMPLESS_NAME( FormatterListIterator ) * iterator )
{
  return NextInFormatterListIterator( iterator );
}
