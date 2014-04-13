#include "private/list/event_attribute.h"

#include "stumpless/list/event_attribute.h"

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( AddSeparatorToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * separator )
{
  return AddSeparatorToEventAttributeList( list, separator );
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( AppendEventAttributeLists )
( __STUMPLESS_NAME( EventAttributeList ) * first, __STUMPLESS_NAME( EventAttributeList ) * second )
{
  return AppendEventAttributeLists( first, second );
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( AppendToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * entry_attribute )
{
  return AppendToEventAttributeList( list, entry_attribute );
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( CopyEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return CopyEventAttributeList( list );
}

void
__STUMPLESS_NAME( DestroyEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  DestroyEventAttributeList( list );
}

unsigned short
__STUMPLESS_NAME( EventAttributeListContains )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * entry_attribute )
{
  return EventAttributeListContains( list, entry_attribute );
}

unsigned short
__STUMPLESS_NAME( EventAttributeListIsEmpty )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return EventAttributeListIsEmpty( list );
}

unsigned
__STUMPLESS_NAME( EventAttributeListSize )
( const __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return EventAttributeListSize( list );
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( NewEventAttributeList )
( void )
{
  return NewEventAttributeList();
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( PrependToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * entry_attribute )
{
  return PrependToEventAttributeList( list, entry_attribute );
}
