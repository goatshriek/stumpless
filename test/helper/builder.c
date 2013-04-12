#include <stdlib.h>

#include <stumpless.h>

#include "builder.h"

StumplessEntry *
BuildEntry( void )
{
  StumplessEntry * entry = malloc( sizeof( StumplessEntry ) );
  if( entry == NULL )
    return NULL;
  
  entry->description = "Test Entry";
  entry->event = BuildEvent();
  entry->attributes = BuildEntryAttributeList();
  entry->attribute_count = 6;
  
  return entry;
}

StumplessEntryAttribute *
BuildEntryAttribute( void )
{
  StumplessEntryAttribute * attribute;
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  
  attribute->event_attribute = BuildEventAttribute();
  attribute->value = StumplessValueFromString( "Test Value" );
  
  return attribute;
}

StumplessEntryAttribute **
BuildEntryAttributeList( void )
{
  StumplessEntryAttribute ** list;
  list = malloc( sizeof( StumplessEntryAttribute * ) * 6 );
  if( list == NULL )
    return NULL;
  
  StumplessEventAttribute ** event_attribute_list = BuildEventAttributeList();
  if( event_attribute_list == NULL )
    return NULL;
  
  StumplessEntryAttribute * attribute;
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[0];
  attribute->value = NULL;
  list[0] = attribute;
  
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[1];
  attribute->value = StumplessValueFromString( "not 37" );
  list[1] = attribute;
  
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[2];
  attribute->value = NULL;
  list[2] = attribute;
  
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = event_attribute_list[3];
  attribute->value = StumplessValueFromString( "unnamed value" );
  list[3] = attribute;
  
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = NULL;
  attribute->value = StumplessValueFromString( "no event attribute" );
  list[4] = attribute;
  
  attribute = malloc( sizeof( StumplessEntryAttribute ) );
  if( attribute == NULL )
    return NULL;
  attribute->event_attribute = NULL;
  attribute->value = NULL;
  list[5] = attribute;
  
  return list;
}

StumplessEvent *
BuildEvent( void )
{
  StumplessEvent * event = malloc( sizeof( StumplessEvent ) );
  if( event == NULL )
    return NULL;
  
  event->name = "Test Event";
  
  event->level = BuildLevel();
  if( event->level == NULL )
    return NULL;
  
  event->attributes = BuildEventAttributeList();
  if( event->attributes == NULL )
    return NULL;
  event->attribute_count = 5;
  
  return event;
}

StumplessEventAttribute *
BuildEventAttribute( void )
{
  StumplessEventAttribute * attribute;
  attribute = malloc( sizeof( StumplessEventAttribute ) );
  if( attribute == NULL )
    return NULL;
  
  attribute->name = "Test Event Attribute";
  attribute->default_value = StumplessValueFromString( "Test Default Value" );
  
  return attribute;
}

StumplessEventAttribute **
BuildEventAttributeList( void )
{
  StumplessEventAttribute ** list;
  list = malloc( sizeof( StumplessEventAttribute * ) * 5 );
  if( list == NULL )
    return NULL;
  
  StumplessEventAttribute * attr_0;
  attr_0 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_0 == NULL )
    return NULL;
  attr_0->name = "Test Attribute 0";
  attr_0->default_value = StumplessValueFromString( "default value" );
  
  StumplessEventAttribute * attr_1;
  attr_1 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_1 == NULL )
    return NULL;
  attr_1->name = NULL;
  attr_1->default_value = StumplessValueFromUnsignedInt( 37 );
  
  StumplessEventAttribute * attr_2;
  attr_2 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_2 == NULL )
    return NULL;
  attr_2->name = "Test Attribute 2";
  attr_2->default_value = NULL;
  
  StumplessEventAttribute * attr_3;
  attr_3 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_3 == NULL )
    return NULL;
  attr_3->name = NULL;
  attr_3->default_value = NULL;
  
  list[0] = attr_0;
  list[1] = attr_1;
  list[2] = attr_2;
  list[3] = attr_3;
  list[4] = NULL;
  
  return list;
}

StumplessLevel *
BuildLevel( void )
{
  StumplessLevel * level = malloc( sizeof( StumplessLevel ) ) ;
  if( level == NULL )
    return NULL;
  
  level->name = "Test Level";
  level->value = 42;
  
  return level;
}

StumplessFormattedOutput *
BuildTextFormattedOutput( void )
{
  StumplessFormattedOutput * output;
  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  
  output->payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( output->payload == NULL )
    return NULL;
  
  output->payload->values = StumplessNewValueList();
  if( output->payload->values == NULL )
    return NULL;
  
  StumplessStatusCode status;
  status = StumplessAppendStringToFormattedOutput( output, "First" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendStringToFormattedOutput( output, " Second" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendStringToFormattedOutput( output, " Third" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  return output;
}
