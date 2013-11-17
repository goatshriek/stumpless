#include <stdio.h>
#include <string.h>

#include "private/configuration.h"
#include "private/handler_list.h"
#include "private/handler_list_static.h"
#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToHandlerList
( HandlerList * list, Handler * handler )
{
  if( list == NULL || handler == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, handler );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Handler *
BeginHandlerList
( HandlerList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

HandlerList *
CopyHandlerList
( HandlerList * list )
{
  if( list == NULL )
    return NULL;
  
  HandlerList * copy = malloc( sizeof( HandlerList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyHandlerList
( HandlerList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
HandlerListIsEmpty
( HandlerList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

HandlerList *
NewHandlerList
( void )
{
  HandlerList * list = malloc( sizeof( HandlerList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Handler *
NextInHandlerList
( HandlerList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

Status *
OutputThroughHandlerList
( HandlerList * list, Output * output )
{
  if( list == NULL || output == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Status * status;
  Handler * handler = BeginList( list->list );
  while( handler != NULL ){
    if( handler->handle == NULL )
      continue;
    
    status = handler->handle( output, handler->options );
    if( status != NULL && status->failure )
      return status;
    
    handler = NextInList( list->list );
  }
  
  return NULL;
}

Status *
PrependToHandlerList
( HandlerList * list, Handler * handler )
{
  if( list == NULL || handler == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, handler );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}
