#include <text_formatter.h>

#include "private/text_formatter.h"

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EntryToText )
( __STUMPLESS_NAME( Entry ) * entry )
{
  return EntryToText( entry );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EntryAttributeToText )
( __STUMPLESS_NAME( EntryAttribute ) * entry_attribute )
{
  return EntryAttributeToText( entry_attribute );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EntryAttributeListToText )
( __STUMPLESS_NAME( Entry ) * entry )
{
  return EntryAttributeListToText( entry );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EntrySummaryToText )
( __STUMPLESS_NAME( Entry ) * entry )
{
  return EntrySummaryToText( entry );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EventToText )
( __STUMPLESS_NAME( Event ) * event )
{
  return EventToText( event );
}

__STUMPLESS_NAME( Output ) * 
__STUMPLESS_NAME( EventAttributeToText )
( __STUMPLESS_NAME( EventAttribute ) * event_attribute )
{
  return EventAttributeToText( event_attribute );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EventAttributeListToText )
( __STUMPLESS_NAME( Event ) * event )
{
  return EventAttributeListToText( event );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( EventSummaryToText )
( __STUMPLESS_NAME( Event ) * event )
{
  return EventSummaryToText( event );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( ArrayValueToText )
( __STUMPLESS_NAME( Value ) * value )
{
  return ArrayValueToText( value );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( SingularValueToText )
( __STUMPLESS_NAME( Value ) * value )
{
  return SingularValueToText( value );
}

__STUMPLESS_NAME( Output ) *
__STUMPLESS_NAME( LevelToText )
( __STUMPLESS_NAME( Level ) * level )
{
  return LevelToText( level );
}
