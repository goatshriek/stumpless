#include "private/configuration.h"
#include "private/formatter_list.h"
#include "private/handler_list.h"
#include "private/list.h"
#include "private/static/formatter_list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToFormatterList
( FormatterList * list, Formatter * formatter )
{
  if( list == NULL || formatter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, formatter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

FormatterList *
CopyFormatterList
( FormatterList * list )
{
  if( list == NULL )
    return NULL;
  
  FormatterList * copy = malloc( sizeof( FormatterList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyFormatterList
( FormatterList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

Status *
EntryThroughFormatterList
( FormatterList * list, Entry * entry )
{
  if( list == NULL || entry == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Status * final_status = NULL;
  Status * handler_status;
  Output * output;
  Formatter * formatter = BeginFormatterList( list );
  while( formatter != NULL ){
    output = formatter->format( entry, formatter->options );
    handler_status = OutputThroughHandlerList( formatter->handlers, output );
    if( handler_status != NULL )
      final_status = handler_status;
    
    formatter = NextInFormatterList( list );
  }
  
  return final_status;
}

unsigned short
FormatterListContains
( FormatterList * list, Formatter * formatter )
{
  return list != NULL && ListContains( list->list, formatter );
}

unsigned short
FormatterListIsEmpty
( FormatterList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

FormatterList *
NewFormatterList
( void )
{
  FormatterList * list = malloc( sizeof( FormatterList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Status *
PrependToFormatterList
( FormatterList * list, Formatter * formatter )
{
  if( list == NULL || formatter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, formatter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}
