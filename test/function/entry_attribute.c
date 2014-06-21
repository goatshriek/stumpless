#include <stdio.h>
#include <stdlib.h>

#include "private/entry_attribute.h"
#include "private/event_attribute.h"
#include "private/type.h"

#include "helper.h"

const char * test_for_event_attribute( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( for_event_attribute )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_for_event_attribute
( void )
{
  EntryAttribute *entry_attribute = EntryAttributeForEventAttribute( NULL );
  if( entry_attribute )
    return "an attribute was created for a null event attribute";
  
  EventAttribute *event_attribute = BuildEventAttribute();
  if( !event_attribute )
    return "could not build a test event attribute";
  
  entry_attribute = EntryAttributeForEventAttribute( event_attribute );
  if( !entry_attribute )
    return "an attribute could not be built from an event attribute";
  
  if( entry_attribute->event_attribute != event_attribute )
    return "the attribute did not have the correct event attribute";
  
  if( entry_attribute->value != event_attribute->default_value )
    return "the attribute did not have the correct value";
  
  return NULL;
}
