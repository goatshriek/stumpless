#include "private/configuration.h"
#include "private/formatter_list.h"
#include "private/formatter_list_static.h"
#include "private/list.h"
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

Formatter *
BeginFormatterList
( FormatterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
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
  return NULL;
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

Formatter *
NextInFormatterList
( FormatterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
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
