#include <stdio.h>
#include <string.h>

#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

#include "private/list/handler.h"
#include "private/list/inheritance.h"
#include "private/list/iterator.h"

#include "private/list/const_iterator/handler.h"

#include "private/list/const_reverse_iterator/handler.h"

#include "private/list/iterator/handler.h"

#include "private/list/reverse_iterator/handler.h"

#include "static/list/handler.h"

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

LIST_CONTAINS( Handler )

LIST_IS_EMPTY( Handler )

LIST_SIZE( Handler )

NEW_LIST( Handler )

Status *
OutputThroughHandlerList
( const HandlerList * list, const Output * output )
{
  if( !list || !output )
    return RaiseAbnormalStatus( "empty argument" );
  
  Status * status;
  Handler * handler;
  ListIterator * handlers = BeginList( list->list );
  while( handler = NextInListIterator( handlers ) ){
    if( !handler->handle )
      continue;
    
    status = handler->handle( output, handler->options );
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
