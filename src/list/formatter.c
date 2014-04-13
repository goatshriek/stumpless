#include <stdlib.h>

#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

#include "private/list/formatter.h"
#include "private/list/handler.h"
#include "private/list/inheritance.h"
#include "private/list/iterator.h"

#include "private/list/const_iterator/formatter.h"

#include "private/list/const_reverse_iterator/formatter.h"

#include "private/list/iterator/formatter.h"

#include "private/list/reverse_iterator/formatter.h"

#include "static/list/formatter.h"

ADD_SEPARATOR_TO_LIST( Formatter )

APPEND_LISTS( Formatter )

APPEND_TO_LIST( Formatter )

BEGIN_LIST( Formatter )

CBEGIN_LIST( Formatter )

CEND_LIST( Formatter )

COPY_LIST( Formatter )

CRBEGIN_LIST( Formatter )

CREND_LIST( Formatter )

DESTROY_LIST( Formatter )

END_LIST( Formatter )

Status *
EntryThroughFormatterList
( const FormatterList * list, const Entry * entry )
{
  if( !list || !entry )
    return RaiseAbnormalStatus( "empty argument" );
  
  Status * final_status = NULL;
  Status * handler_status;
  Output * output;
  Formatter * formatter;
  ListIterator * formatters = BeginList( list->list );
  while( formatter = NextInListIterator( formatters ) ){
    output = formatter->format( entry, formatter->options );
    handler_status = OutputThroughHandlerList( formatter->handlers, output );
    if( handler_status )
      final_status = handler_status;
  }
  
  return final_status;
}

LIST_CONTAINS( Formatter )

LIST_IS_EMPTY( Formatter )

LIST_SIZE( Formatter )

NEW_LIST( Formatter )

PREPEND_TO_LIST( Formatter )

RBEGIN_LIST( Formatter )

REND_LIST( Formatter )
