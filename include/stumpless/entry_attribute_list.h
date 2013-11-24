#ifndef __STUMPLESS_ENTRY_ATTRIBUTE_LIST_H
#define __STUMPLESS_ENTRY_ATTRIBUTE_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) *, __STUMPLESS_NAME( EntryAttribute ) * );

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( BeginEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * );

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( CopyEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * );

void
__STUMPLESS_NAME( DestroyEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * );

unsigned short
__STUMPLESS_NAME( EntryAttributeListIsEmpty )
( __STUMPLESS_NAME( EntryAttributeList ) * );

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( NewEntryAttributeList )
( void );

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( NextInEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) *, __STUMPLESS_NAME( EntryAttribute ) * );

#endif
