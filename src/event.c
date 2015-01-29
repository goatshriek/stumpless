#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/event.h>
#include <stumpless/exception.h>
#include <stumpless/formatter/text.h>

#include "private/container/dictionary.h"
#include "private/container/list/value.h"
#include "private/event/initializer.h"
#include "private/formatter.h"
#include "private/level.h"
#include "private/output.h"
#include "private/type.h"

static Dictionary *events = NULL; /**< currently initialized events (by name) */

Event *
AddEvent
( Event *event )
{
  if( !event || !event->name )
    return event;

  if( !events ){
    events = NewDictionary();

    // todo throw dictionary constructor failure
    if( !events )
      return event;
  }

  SetDictionaryValue( events, event->name, event );

  return event;
}

char *
EventToString
( Event *event )
{
  return OutputToString( EventToText( FindFormatterByName( "text" ), event ) );
}

Event *
FindEventByName
( const char *name )
{
  Event *event;

  if( !events ){
    events = NewDictionary();

    if( !events )
      return NULL;
  }

  event = GetDictionaryValue( events, name );

  if( !event )
    return InitializeEventByName( name );

  return event;
}
