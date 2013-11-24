#ifndef __STUMPLESS_EVENT_ATTRIBUTE_LIST_H
#define __STUMPLESS_EVENT_ATTRIBUTE_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) *, __STUMPLESS_NAME( EventAttribute ) * );

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( BeginEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * );

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( CopyEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * );

void
__STUMPLESS_NAME( DestroyEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * );

unsigned short
__STUMPLESS_NAME( EventAttributeListIsEmpty )
( __STUMPLESS_NAME( EventAttributeList ) * );

__STUMPLESS_NAME( EventAttributeList ) *
__STUMPLESS_NAME( NewEventAttributeList )
( void );

__STUMPLESS_NAME( EventAttribute ) *
__STUMPLESS_NAME( NextInEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToEventAttributeList )
( __STUMPLESS_NAME( EventAttributeList ) *, __STUMPLESS_NAME( EventAttribute ) * );

#endif
