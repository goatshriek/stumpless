#include <stdlib.h>

#include <stumpless.h>

#include "builder.h"

StumplessBoolean *
BuildBoolean( void )
{
  StumplessBoolean * boolean = malloc( sizeof( StumplessBoolean ) );
  if( boolean == NULL )
    return NULL;
  
  boolean->format = malloc( sizeof( StumplessBooleanFormat ) );
  if( boolean->format == NULL )
    return NULL;
  
  boolean->value = 1;
  boolean->format->true_description = "true";
  boolean->format->false_description = "false";
  
  return boolean;
}

StumplessValue *
BuildBooleanValue( void )
{
  StumplessBoolean * boolean = BuildBoolean();
  if( boolean == NULL )
    return NULL;
  
  StumplessValue * value = StumplessValueFromBoolean( boolean );
  if( value == NULL )
    return NULL;
  
  return value;
}

StumplessFormattedOutput *
BuildByteFormattedOutput( void )
{
  StumplessFormattedOutput * output;
  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  output->format = STUMPLESS_BINARY;
  
  return output;
}

StumplessValue *
BuildCharArrayValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->profile = StumplessFindProfileByName( "Char Array" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  char * array = malloc( sizeof( char ) * 10 );
  if( array == NULL )
    return NULL;
  
  array[0] = 'a';
  array[1] = 'b';
  array[2] = 'c';
  array[3] = 'd';
  array[4] = 'e';
  array[5] = 'f';
  array[6] = 'g';
  array[7] = 'h';
  array[8] = 'i';
  array[9] = 'j';
  
  value->data->c_p = array;
  value->length = 10;
  
  return value;
}

StumplessValue *
BuildEmptyUnsignedIntArrayValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->type = STUMPLESS_UNSIGNED_INT_POINTER; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Int" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = NULL;
  value->length = 0;
  
  return value;
}

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

StumplessValue *
BuildIntArrayValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->format = NULL;
  value->type = STUMPLESS_INT_POINTER; // todo remove
  
  value->profile = StumplessFindProfileByName( "Int Array" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  int * array = malloc( sizeof( int ) * 10 );
  if( array == NULL )
    return NULL;
  
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  array[3] = 3;
  array[4] = 4;
  array[5] = 5;
  array[6] = 6;
  array[7] = 7;
  array[8] = 8;
  array[9] = 9;
  
  value->data->i_p = array;
  value->length = 10;
  
  return value;
}

StumplessValue *
BuildIntValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->type = STUMPLESS_INT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Int" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->i = 45678;
  
  return value;
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

StumplessValue *
BuildStringValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue * ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->type = STUMPLESS_STRING; // todo remove
  
  value->profile = StumplessFindProfileByName( "String" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->c_p = "Test String Value";
  
  return value;
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
  
  StumplessValueList * values = StumplessNewValueList();
  if( values == NULL )
    return NULL;
  
  StumplessStatusCode status;
  status = StumplessAppendStringToValueList( values, "First\n" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendStringToValueList( values, "Second\n" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendStringToValueList( values, "Third" );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  output->payload->values = values;
  
  return output;
}

StumplessTypeProfile *
BuildTypeProfile( void )
{
  StumplessTypeProfile * profile = malloc( sizeof( StumplessTypeProfile ) );
  if( profile == NULL )
    return NULL;
  
  profile->name = "Test Profile";
  profile->to_binary = NULL;
  profile->to_csv = NULL;
  profile->to_json = NULL;
  profile->to_string = NULL;
  profile->to_text = NULL;
  profile->to_value_list = NULL;
  profile->to_xml = NULL;
  
  return profile;
}

StumplessValue *
BuildUnsignedIntValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->format = NULL;
  value->type = STUMPLESS_UNSIGNED_INT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Int" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  value->data->u_i = 4294967196u;
  
  return value;
}

StumplessValue *
BuildUnsignedShortValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->format = NULL;
  value->type = STUMPLESS_UNSIGNED_SHORT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Short" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  value->data->u_s = 65000u;
  
  return value;
}

StumplessValueList *
BuildValueList( void )
{
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  StumplessStatusCode status;
  StumplessValue * value;
  
  value = BuildIntArrayValue();
  if( value == NULL )
    return NULL;
  status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  value = BuildUnsignedIntValue();
  if( value == NULL )
    return NULL;
  status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  value = BuildUnsignedShortValue();
  if( value == NULL )
    return NULL;
  status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  value = BuildCharArrayValue();
  if( value == NULL )
    return NULL;
  status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  value = BuildVoidValue();
  if( value == NULL )
    return NULL;
  status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  return list;
}

StumplessValueList *
BuildValueListOfStrings( void )
{
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  StumplessAppendStringToValueList( list, "this" );
  StumplessAppendStringToValueList( list, "is" );
  StumplessAppendStringToValueList( list, "a" );
  StumplessAppendStringToValueList( list, "test" );
  StumplessAppendStringToValueList( list, "list" );
  
  return list;
}

StumplessValue *
BuildVoidValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->type = STUMPLESS_VOID_POINTER; // todo remove
  value->profile = StumplessFindProfileByName( "Boolean" );
  if( value->profile == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
 
  StumplessBoolean * boolean = BuildBoolean();
  if( boolean == NULL )
    return NULL;
   
  value->data->v_p = (void *) boolean;
  
  return value;
}
