#include <stdlib.h>

#include "private/entry_attribute.h"
#include "private/list.h"
#include "private/type.h"

#include "private/list/entry_attribute.h"
#include "private/list/event_attribute.h"
#include "private/list/iterator.h"
#include "private/list/inheritance.h"

#include "private/list/const_iterator/entry_attribute.h"
#include "private/list/const_iterator/event_attribute.h"

#include "private/list/const_reverse_iterator/entry_attribute.h"

#include "private/list/iterator/entry_attribute.h"

#include "private/list/reverse_iterator/entry_attribute.h"

#include "static/list/entry_attribute.h"

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

LIST_CONTAINS( EntryAttribute )

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
  
  ListIterator * primary_attributes = BeginList( primary->list );
  ListIterator * secondary_attributes = BeginList( secondary->list );
  
  EntryAttribute * primary_attribute;
  EntryAttribute * secondary_attribute;

  unsigned short matched;
  
  while( secondary_attribute = NextInListIterator( secondary_attributes ) ){
    matched = 0;
    // todo put this search into it's own function to remove the matched variable
    while( primary_attribute = NextInListIterator( primary_attributes ) ){
      if( primary_attribute->event_attribute == secondary_attribute->event_attribute ){
        matched = 1;
        break;
      }
    }
    
    if( !matched )
      AppendToEntryAttributeList( primary, secondary_attribute );
  }
  
  return primary;
}

NEW_LIST( EntryAttribute )

PREPEND_TO_LIST( EntryAttribute )

RBEGIN_LIST( EntryAttribute )

REND_LIST( EntryAttribute )
