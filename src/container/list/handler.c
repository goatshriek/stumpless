#include <stdio.h>
#include <string.h>

#include <stumpless/exception.h>

#include "private/container/list.h"
#include "private/container/list/const_iterator/handler.h"
#include "private/container/list/const_reverse_iterator/handler.h"
#include "private/container/list/handler.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/iterator/handler.h"
#include "private/container/list/reverse_iterator/handler.h"
#include "private/type.h"
#include "static/container/list/handler.h"

ADD_SEPARATOR_TO_LIST( Handler )

APPEND_LISTS( Handler )

APPEND_TO_LIST( Handler )

BEGIN_LIST( Handler )

CBEGIN_LIST( Handler )

CEND_LIST( Handler )

COPY_LIST( Handler )

CRBEGIN_LIST( Handler )

CREND_LIST( Handler )

DESTROY_LIST( Handler )

END_LIST( Handler )

LIST_BACK( Handler )

LIST_CONTAINS( Handler )

LIST_FRONT( Handler )

LIST_IS_EMPTY( Handler )

LIST_SIZE( Handler )

NEW_LIST( Handler )

const HandlerList *
OutputThroughHandlerList
( const HandlerList *list, const Output *output )
{
  Handler *handler;
  ListIterator *handlers;

  if( !list || !output )
    return list;

  handlers = BeginList( list->list );
  while( handler = NextInListIterator( handlers ) ){
    if( !handler->handle )
      continue;

    handler->handle( handler, output );
  }

  DestroyListIterator( handlers );
  return list;
}

PREPEND_TO_LIST( Handler )

RBEGIN_LIST( Handler )

REND_LIST( Handler )
