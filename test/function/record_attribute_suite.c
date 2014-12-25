#include <stdio.h>
#include <stdlib.h>

#include <stumpless/record_attribute.h>

#include "private/event_attribute.h"
#include "private/type.h"

#include "test/helper.h"

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
  RecordAttribute *record_attribute = NewRecordAttributeForEventAttribute( NULL );
  if( record_attribute )
    return "an attribute was created for a null event attribute";
  
  EventAttribute *event_attribute = BuildEventAttribute();
  if( !event_attribute )
    return "could not build a test event attribute";
  
  record_attribute = NewRecordAttributeForEventAttribute( event_attribute );
  if( !record_attribute )
    return "an attribute could not be built from an event attribute";
  
  if( record_attribute->event_attribute != event_attribute )
    return "the attribute did not have the correct event attribute";
  
  if( record_attribute->value != event_attribute->default_value )
    return "the attribute did not have the correct value";
  
  return NULL;
}
