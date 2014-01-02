#include "private/configuration.h"
#include "private/event_attribute_list.h"
#include "private/list.h"
#include "private/static/event_attribute_list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToEventAttributeList
( EventAttributeList * list, EventAttribute * attribute )
{
  if( list == NULL || attribute == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, attribute );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

EventAttribute *
BeginEventAttributeList
( EventAttributeList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

EventAttributeList *
CopyEventAttributeList
( EventAttributeList * list )
{
  if( list == NULL )
    return NULL;
  
  EventAttributeList * copy = malloc( sizeof( EventAttributeList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyEventAttributeList
( EventAttributeList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
EventAttributeListIsEmpty
( EventAttributeList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

EventAttributeList *
NewEventAttributeList
( void )
{
  EventAttributeList * list = malloc( sizeof( EventAttributeList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

EventAttribute *
NextInEventAttributeList
( EventAttributeList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

Status *
PrependToEventAttributeList
( EventAttributeList * list, EventAttribute * attribute )
{
  if( list == NULL || attribute == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, attribute );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}
