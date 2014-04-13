#include "private/list/entry_attribute.h"

#include "stumpless/list/entry_attribute.h"

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( AddSeparatorToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * separator )
{
  return AddSeparatorToEntryAttributeList( list, separator );
}

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( AppendEntryAttributeLists )
( __STUMPLESS_NAME( EntryAttributeList ) * first, __STUMPLESS_NAME( EntryAttributeList ) * second )
{
  return AppendEntryAttributeLists( first, second );
}

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( AppendToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * entry_attribute )
{
  return AppendToEntryAttributeList( list, entry_attribute );
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
__STUMPLESS_NAME( EntryAttributeListContains )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * entry_attribute )
{
  return EntryAttributeListContains( list, entry_attribute );
}

unsigned short
__STUMPLESS_NAME( EntryAttributeListIsEmpty )
( __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return EntryAttributeListIsEmpty( list );
}

unsigned
__STUMPLESS_NAME( EntryAttributeListSize )
( const __STUMPLESS_NAME( EntryAttributeList ) * list )
{
  return EntryAttributeListSize( list );
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

__STUMPLESS_NAME( EntryAttributeList ) *
__STUMPLESS_NAME( PrependToEntryAttributeList )
( __STUMPLESS_NAME( EntryAttributeList ) * list, __STUMPLESS_NAME( EntryAttribute ) * entry_attribute )
{
  return PrependToEntryAttributeList( list, entry_attribute );
}
