#include "private/entry_attribute.h"
#include "private/type.h"

// todo implement
void
DestroyEntryAttribute
( EntryAttribute *attribute )
{
  return;
}

EntryAttribute *
EntryAttributeForEventAttribute
( const EventAttribute *event_attribute )
{
  if( !event_attribute )
    return NULL;

  EntryAttribute *entry_attribute = malloc( sizeof( EntryAttribute ) );
  if( !entry_attribute )
    return NULL;

  entry_attribute->event_attribute = event_attribute;
  entry_attribute->value = event_attribute->default_value;

  return entry_attribute;
}
