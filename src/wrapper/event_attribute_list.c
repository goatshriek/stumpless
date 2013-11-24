#include "stumpless/event_attribute_list.h"

#include "private/event_attribute_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * attribute )
{
  return AppendToEventAttributeList( list, attribute );
}

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( BeginEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return BeginEventAttributeList( list );
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
__STUMPLESS_NAME( EventAttributeListIsEmpty )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return EventAttributeListIsEmpty( list );
}

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( NewEventAttributeList )
( void )
{
  return NewEventAttributeList();
}

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( NextInEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list )
{
  return NextInEventAttributeList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * list, __STUMPLESS_NAME( EventAttribute ) * attribute )
{
  return PrependToEventAttributeList( list, attribute );
}
