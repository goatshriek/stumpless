#include "private/record_attribute.h"
#include "private/type.h"

// todo implement
void
DestroyRecordAttribute
( RecordAttribute *attribute )
{
  return;
}

RecordAttribute *
RecordAttributeForEventAttribute
( const EventAttribute *event_attribute )
{
  if( !event_attribute )
    return NULL;

  RecordAttribute *record_attribute = malloc( sizeof( RecordAttribute ) );
  if( !record_attribute )
    return NULL;

  record_attribute->event_attribute = event_attribute;
  record_attribute->value = event_attribute->default_value;

  return record_attribute;
}
