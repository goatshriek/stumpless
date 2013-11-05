#include <filter_list.h>

#include "private/filter_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToFilterList )
( __STUMPLESS_NAME( FilterList ) * list, __STUMPLESS_NAME( Filter ) * filter )
{
  return AppendToFilterList( list, filter );
}

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( BeginFilterList )
( __STUMPLESS_NAME( FilterList ) * list )
{
  return BeginFilterList( list );
}

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( CopyFilterList )
( __STUMPLESS_NAME( FilterList ) * list )
{
  return CopyFilterList( list );
}

void
__STUMPLESS_NAME( DestroyFilterList )
( __STUMPLESS_NAME( FilterList ) * list )
{
  DestroyFilterList( list );
}

unsigned short
__STUMPLESS_NAME( EntryThroughFilterList )
( __STUMPLESS_NAME( FilterList ) * list, __STUMPLESS_NAME( Entry ) * entry )
{
  return EntryThroughFilterList( list, entry );
}

unsigned short
__STUMPLESS_NAME( FilterListIsEmpty )
( __STUMPLESS_NAME( FilterList ) * list )
{
  return FilterListIsEmpty( list );
}

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( NewFilterList )
( void )
{
  return NewFilterList();
}

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( NextInFilterList )
( __STUMPLESS_NAME( FilterList ) * list )
{
  return NextInFilterList( list );
}

unsigned short
__STUMPLESS_NAME( OutputThroughFilterList )
( __STUMPLESS_NAME( FilterList ) * list, __STUMPLESS_NAME( Output ) * output )
{
  return OutputThroughFilterList( list, output );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToFilterList )
( __STUMPLESS_NAME( FilterList ) * list, __STUMPLESS_NAME( Filter ) * filter )
{
  return PrependToFilterList( list, filter );
}

unsigned short
__STUMPLESS_NAME( ValueThroughFilterList )
( __STUMPLESS_NAME( FilterList ) * list, __STUMPLESS_NAME( Value ) * value )
{
  return ValueThroughFilterList( list, value );
}
