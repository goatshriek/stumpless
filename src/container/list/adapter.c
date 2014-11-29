#include <stdlib.h>

#include <stumpless/record.h>

#include "private/container/list/adapter.h"
#include "private/container/list/const_iterator/adapter.h"
#include "private/container/list/const_reverse_iterator/adapter.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/iterator/adapter.h"
#include "private/container/list/reverse_iterator/adapter.h"
#include "private/type.h"
#include "static/container/list/adapter.h"

LIST_BACK( Adapter )

LIST_CONTAINS( Adapter )

LIST_FRONT( Adapter )

LIST_IS_EMPTY( Adapter )

LIST_SIZE( Adapter )

ADD_SEPARATOR_TO_LIST( Adapter )

APPEND_LISTS( Adapter )

APPEND_TO_LIST( Adapter )

BEGIN_LIST( Adapter )

CBEGIN_LIST( Adapter )

CEND_LIST( Adapter )

COPY_LIST( Adapter )

CRBEGIN_LIST( Adapter )

CREND_LIST( Adapter )

DESTROY_LIST( Adapter )

END_LIST( Adapter )

Record *
RecordThroughAdapterList
( const AdapterList *list, Record *record )
{
  Adapter *adapter;
  ListIterator *iterator;

  if( !list || !record )
    return NULL;

  iterator = BeginList( list->list );
  while( adapter = NextInListIterator( iterator ) ) {
    adapter->adapt( adapter, record );
  }

  DestroyListIterator( iterator );

  return record;
}

NEW_LIST( Adapter )

PREPEND_TO_LIST( Adapter )

RBEGIN_LIST( Adapter )

REND_LIST( Adapter )
