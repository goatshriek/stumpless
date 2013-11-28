#include "stumpless/entry_attribute_list.h"

#include "private/entry_attribute_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * attribute )
{
  return AppendToEntryAttributeList( list, attribute );
}

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( BeginEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return BeginEntryAttributeList( list );
}

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( CopyEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return CopyEntryAttributeList( list );
}

void
__STUMPLESS_NAME( DestroyEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  DestroyEntryAttributeList( list );
}

unsigned short
__STUMPLESS_NAME( EntryAttributeListIsEmpty )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return EntryAttributeListIsEmpty( list );
}

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( MergeEntryAttributeLists )
( __STUMPLESS_NAME( EntryAttributeList ) * primary, __STUMPLESS_NAME( EntryAttributeList ) * secondary )
{
  return MergeEntryAttributeLists( primary, secondary );
}

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( NewEntryAttributeList )
( void )
{
  return NewEntryAttributeList();
}

__STUMPLESS_NAME( EntryAttribute ) *
__STUMPLESS_NAME( NextInEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return NextInEntryAttributeList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * attribute )
{
  return PrependToEntryAttributeList( list, attribute );
}
