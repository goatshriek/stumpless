#include <stdio.h>
#include <string.h>

#include "private/container/list.h"
#include "private/type.h"

#include "private/container/list/filter.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"

#include "private/container/list/const_iterator/filter.h"

#include "private/container/list/const_reverse_iterator/filter.h"

#include "private/container/list/iterator/filter.h"

#include "private/container/list/reverse_iterator/filter.h"

#include "static/container/list/filter.h"

ADD_SEPARATOR_TO_LIST( Filter )

APPEND_LISTS( Filter )

APPEND_TO_LIST( Filter )

BEGIN_LIST( Filter )

CBEGIN_LIST( Filter )

CEND_LIST( Filter )

COPY_LIST( Filter )

CRBEGIN_LIST( Filter )

CREND_LIST( Filter )

DESTROY_LIST( Filter )

END_LIST( Filter )

unsigned short
EntryThroughFilterList
( const FilterList * list, const Entry * entry )
{
  if( !list )
    return 1;

  Filter * filter;
  ListIterator * filters = BeginList( list->list );
  while( filter = NextInListIterator( filters ) ){
    if( !filter->accept_entry( entry, filter->options ) ){
      DestroyListIterator( filters );
      return 0;
    }
  }

  DestroyListIterator( filters );

  return 1;
}

LIST_BACK( Filter )

LIST_CONTAINS( Filter )

LIST_FRONT( Filter )

LIST_IS_EMPTY( Filter )

LIST_SIZE( Filter )

NEW_LIST( Filter )

// todo implement
unsigned short
OutputThroughFilterList
( const FilterList * list, const Output * output )
{
  return 0;
}

PREPEND_TO_LIST( Filter )

RBEGIN_LIST( Filter )

REND_LIST( Filter )

// todo implement
unsigned short
ValueThroughFilterList
( const FilterList * list, const Value * value )
{
  return 0;
}
