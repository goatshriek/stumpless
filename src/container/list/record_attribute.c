#include <stdlib.h>

#include "private/record_attribute.h"
#include "private/container/list.h"
#include "private/container/list/record_attribute.h"
#include "private/container/list/event_attribute.h"
#include "private/container/list/iterator.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/const_iterator.h"
#include "private/container/list/const_iterator/record_attribute.h"
#include "private/container/list/const_iterator/event_attribute.h"
#include "private/container/list/const_reverse_iterator/record_attribute.h"
#include "private/container/list/iterator/record_attribute.h"
#include "private/container/list/reverse_iterator/record_attribute.h"
#include "private/type.h"
#include "static/container/list/record_attribute.h"

ADD_SEPARATOR_TO_LIST( RecordAttribute )

APPEND_LISTS( RecordAttribute )

APPEND_TO_LIST( RecordAttribute )

BEGIN_LIST( RecordAttribute )

CBEGIN_LIST( RecordAttribute )

CEND_LIST( RecordAttribute )

COPY_LIST( RecordAttribute )

CRBEGIN_LIST( RecordAttribute )

CREND_LIST( RecordAttribute )

DESTROY_LIST( RecordAttribute )

END_LIST( RecordAttribute )

LIST_BACK( RecordAttribute )

LIST_CONTAINS( RecordAttribute )

unsigned short
RecordAttributeListContainsEventAttribute
( const RecordAttributeList *list, const EventAttribute *event_attribute )
{
  if( !list || !event_attribute )
    return 0;

  ListConstIterator *record_attributes = CBeginList( list->list );
  const RecordAttribute *record_attribute;
  while( record_attribute = NextInListConstIterator( record_attributes ) ){
    if( record_attribute->event_attribute == event_attribute )
      return 1;
  }

  DestroyListConstIterator( record_attributes );

  return 0;
}

RecordAttributeList *
RecordAttributeListForEventAttributeList
( const EventAttributeList *event_attribute_list )
{
  if( !event_attribute_list )
    return NULL;

  RecordAttributeList *record_attribute_list = NewRecordAttributeList();
  if( !record_attribute_list )
    return NULL;

  RecordAttribute *record_attribute;
  const EventAttribute *event_attribute;
  EventAttributeListConstIterator *event_attributes = CBeginEventAttributeList( event_attribute_list );
  while( event_attribute = NextInEventAttributeListConstIterator( event_attributes ) ){
    record_attribute = RecordAttributeForEventAttribute( event_attribute );
    AppendToRecordAttributeList( record_attribute_list, record_attribute );
  }

  return record_attribute_list;
}

LIST_FRONT( RecordAttribute )

LIST_IS_EMPTY( RecordAttribute )

LIST_SIZE( RecordAttribute )

RecordAttributeList *
MergeRecordAttributeLists
( RecordAttributeList * primary, RecordAttributeList * secondary )
{
  if( !primary )
    return secondary;

  if( !secondary )
    return primary;

  ListIterator * attributes = BeginList( secondary->list );
  RecordAttribute * attribute;

  while( attribute = NextInListIterator( attributes ) ){
    if( RecordAttributeListContainsEventAttribute( primary, attribute->event_attribute ) )
      AppendToRecordAttributeList( primary, attribute );
  }

  DestroyListIterator( attributes );

  return primary;
}

NEW_LIST( RecordAttribute )

PREPEND_TO_LIST( RecordAttribute )

RBEGIN_LIST( RecordAttribute )

REND_LIST( RecordAttribute )
