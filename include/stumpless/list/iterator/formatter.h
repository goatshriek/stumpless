#ifndef __STUMPLESS_LIST_ITERATOR_FORMATTER_H
#define __STUMPLESS_LIST_ITERATOR_FORMATTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( FormatterListIteratorHasNext )
( const __STUMPLESS_NAME( FormatterListIterator ) * );

__STUMPLESS_NAME( FormatterListIterator ) *
__STUMPLESS_NAME( CopyFormatterListIterator )
( const __STUMPLESS_NAME( FormatterListIterator ) * );

void
__STUMPLESS_NAME( DestroyFormatterListIterator )
( __STUMPLESS_NAME( FormatterListIterator ) * );

__STUMPLESS_NAME( FormatterListIterator ) *
__STUMPLESS_NAME( NewFormatterListIterator )
( __STUMPLESS_NAME( FormatterList ) * );

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( NextInFormatterListIterator )
( __STUMPLESS_NAME( FormatterListIterator ) * );

#endif
