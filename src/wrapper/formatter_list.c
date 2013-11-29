#include "stumpless/formatter_list.h"

#include "private/formatter_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list, __STUMPLESS_NAME( Formatter ) * formatter )
{
  return AppendToFormatterList( list, formatter );
}

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( BeginFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  return BeginFormatterList( list );
}

__STUMPLESS_NAME( FormatterList ) *
__STUMPLESS_NAME( CopyFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  return CopyFormatterList( list );
}

void
__STUMPLESS_NAME( DestroyFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  DestroyFormatterList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( EntryThroughFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list, __STUMPLESS_NAME( Entry ) * entry )
{
  return EntryThroughFormatterList( list, entry );
}

unsigned short
__STUMPLESS_NAME( FormatterListContains )
( __STUMPLESS_NAME( FormatterList ) * list, __STUMPLESS_NAME( Formatter ) * formatter )
{
  return FormatterListContains( list, formatter );
}

unsigned short
__STUMPLESS_NAME( FormatterListIsEmpty )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  return FormatterListIsEmpty( list );
}

__STUMPLESS_NAME( FormatterList ) *
__STUMPLESS_NAME( NewFormatterList )
( void )
{
  return NewFormatterList();
}

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( NextInFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list )
{
  return NextInFormatterList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToFormatterList )
( __STUMPLESS_NAME( FormatterList ) * list, __STUMPLESS_NAME( Formatter ) * formatter )
{
  return PrependToFormatterList( list, formatter );
}
