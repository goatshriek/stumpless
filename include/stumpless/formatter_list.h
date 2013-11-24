#ifndef __STUMPLESS_FORMATTER_LIST_H
#define __STUMPLESS_FORMATTER_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToFormatterList )
( __STUMPLESS_NAME( FormatterList ) *, __STUMPLESS_NAME( Formatter ) * );

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( BeginFormatterList )
( __STUMPLESS_NAME( FormatterList ) * );

__STUMPLESS_NAME( FormatterList ) *
__STUMPLESS_NAME( CopyFormatterList )
( __STUMPLESS_NAME( FormatterList ) * );

void
__STUMPLESS_NAME( DestroyFormatterList )
( __STUMPLESS_NAME( FormatterList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( EntryThroughFormatterList )
( __STUMPLESS_NAME( FormatterList ) *, __STUMPLESS_NAME( Entry ) * );

unsigned short
__STUMPLESS_NAME( FormatterListIsEmpty )
( __STUMPLESS_NAME( FormatterList ) * );

__STUMPLESS_NAME( FormatterList ) *
__STUMPLESS_NAME( NewFormatterList )
( void );

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( NextInFormatterList )
( __STUMPLESS_NAME( FormatterList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToFormatterList )
( __STUMPLESS_NAME( FormatterList ) *, __STUMPLESS_NAME( Formatter ) * );

#endif
