#include <stdlib.h>

#include "private/entry_attribute.h"
#include "private/container/list.h"
#include "private/container/list/entry_attribute.h"
#include "private/container/list/event_attribute.h"
#include "private/container/list/iterator.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/const_iterator.h"
#include "private/container/list/const_iterator/entry_attribute.h"
#include "private/container/list/const_iterator/event_attribute.h"
#include "private/container/list/const_reverse_iterator/entry_attribute.h"
#include "private/container/list/iterator/entry_attribute.h"
#include "private/container/list/reverse_iterator/entry_attribute.h"
#include "private/type.h"
#include "static/container/list/entry_attribute.h"

ADD_SEPARATOR_TO_LIST( EntryAttribute )

APPEND_LISTS( EntryAttribute )

APPEND_TO_LIST( EntryAttribute )

BEGIN_LIST( EntryAttribute )

CBEGIN_LIST( EntryAttribute )

CEND_LIST( EntryAttribute )

COPY_LIST( EntryAttribute )

CRBEGIN_LIST( EntryAttribute )

CREND_LIST( EntryAttribute )

DESTROY_LIST( EntryAttribute )

END_LIST( EntryAttribute )

LIST_BACK( EntryAttribute )

LIST_CONTAINS( EntryAttribute )

unsigned short
EntryAttributeListContainsEventAttribute
( const EntryAttributeList *list, const EventAttribute *event_attribute )
{
  if( !list || !event_attribute )
    return 0;

  ListConstIterator *entry_attributes = CBeginList( list->list );
  const EntryAttribute *entry_attribute;
  while( entry_attribute = NextInListConstIterator( entry_attributes ) ){
    if( entry_attribute->event_attribute == event_attribute )
      return 1;
  }

  DestroyListConstIterator( entry_attributes );

  return 0;
}

EntryAttributeList *
EntryAttributeListForEventAttributeList
( const EventAttributeList *event_attribute_list )
{
  if( !event_attribute_list )
    return NULL;

  EntryAttributeList *entry_attribute_list = NewEntryAttributeList();
  if( !entry_attribute_list )
    return NULL;

  EntryAttribute *entry_attribute;
  const EventAttribute *event_attribute;
  EventAttributeListConstIterator *event_attributes = CBeginEventAttributeList( event_attribute_list );
  while( event_attribute = NextInEventAttributeListConstIterator( event_attributes ) ){
    entry_attribute = EntryAttributeForEventAttribute( event_attribute );
    AppendToEntryAttributeList( entry_attribute_list, entry_attribute );
  }

  return entry_attribute_list;
}

LIST_FRONT( EntryAttribute )

LIST_IS_EMPTY( EntryAttribute )

LIST_SIZE( EntryAttribute )

EntryAttributeList *
MergeEntryAttributeLists
( EntryAttributeList * primary, EntryAttributeList * secondary )
{
  if( !primary )
    return secondary;

  if( !secondary )
    return primary;

  ListIterator * attributes = BeginList( secondary->list );
  EntryAttribute * attribute;

  while( attribute = NextInListIterator( attributes ) ){
    if( EntryAttributeListContainsEventAttribute( primary, attribute->event_attribute ) )
      AppendToEntryAttributeList( primary, attribute );
  }

  DestroyListIterator( attributes );

  return primary;
}

NEW_LIST( EntryAttribute )

PREPEND_TO_LIST( EntryAttribute )

RBEGIN_LIST( EntryAttribute )

REND_LIST( EntryAttribute )
