#include <stdio.h>
#include <string.h>

#include "private/container/list.h"
#include "private/status.h"
#include "private/type.h"

#include "private/container/list/handler.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/const_iterator/handler.h"
#include "private/container/list/const_reverse_iterator/handler.h"
#include "private/container/list/iterator/handler.h"
#include "private/container/list/reverse_iterator/handler.h"
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

Status *
OutputThroughHandlerList
( const HandlerList *list, const Output *output )
{
  Handler *handler;
  ListIterator *handlers;
  Status *status;

  if( !list || !output )
    return RaiseStatus( "empty argument" );

  handlers = BeginList( list->list );
  while( handler = NextInListIterator( handlers ) ){
    if( !handler->handle )
      continue;

    status = handler->handle( handler, output );
    if( status && status->failure ){
      DestroyListIterator( handlers );
      return status;
    }
  }

  DestroyListIterator( handlers );
  return NULL;
}

PREPEND_TO_LIST( Handler )

RBEGIN_LIST( Handler )

REND_LIST( Handler )
