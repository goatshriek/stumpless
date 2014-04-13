#include <stdlib.h>

#include "private/entry.h"
#include "private/type.h"

#include "private/list/adapter.h"
#include "private/list/inheritance.h"
#include "private/list/iterator.h"

#include "private/list/const_iterator/adapter.h"

#include "private/list/const_reverse_iterator/adapter.h"

#include "private/list/iterator/adapter.h"

#include "private/list/reverse_iterator/adapter.h"

#include "static/list/adapter.h"

LIST_CONTAINS( Adapter )

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

NEW_LIST( Adapter )

PREPEND_TO_LIST( Adapter )

RBEGIN_LIST( Adapter )

REND_LIST( Adapter )

Entry *
ValueThroughAdapterList
( AdapterList * list, Value * value )
{
  if( !list || !value )
    return NULL;
  
  Entry * entry;
  Adapter * adapter;
  ListIterator * iterator = BeginList( list->list );
  while( adapter = NextInListIterator( iterator ) ) {
    entry = MergeEntries( entry, adapter->adapt( value, adapter->options ) );
  }
  
  DestroyListIterator( iterator );
  
  return entry;
}
