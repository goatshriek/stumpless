#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <configuration.h>
#include <formatted_output.h>
#include <status_checker.h>
#include <text_formatter.h>
#include <text_formatter_static.h>
#include <type.h>
#include <value.h>
#include <value_constructor.h>
#include <value_list.h>

StumplessFormattedOutput *
StumplessBooleanArrayValueAsText( StumplessValue * value )
{
  StumplessValueList * output = BooleanArrayValueAsValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessBooleanValueAsText( StumplessValue * value )
{
  StumplessValueList * output = BooleanValueAsValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * entry )
{
  return TextFormattedOutputFromValueList( EntryAsValueList( entry ) );
}

StumplessFormattedOutput *
StumplessEntryAttributeAsText( StumplessEntryAttribute * attribute )
{
  StumplessValueList * output = EntryAttributeAsValueList( attribute );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEntryAttributeListAsText( StumplessEntry * entry )
{
  StumplessValueList * output = EntryAttributeListAsValueList( entry );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEntrySummaryAsText( StumplessEntry * entry )
{
  return TextFormattedOutputFromValueList( EntrySummaryAsValueList( entry ) );
}

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * event )
{
  return TextFormattedOutputFromValueList( EventAsValueList( event ) );
}

StumplessFormattedOutput *
StumplessEventAttributeAsText( StumplessEventAttribute * attribute )
{
  StumplessValueList * output = EventAttributeAsValueList( attribute );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEventAttributeListAsText( StumplessEvent * event )
{
  StumplessValueList * output = EventAttributeListAsValueList( event );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEventSummaryAsText( StumplessEvent * event )
{
  return TextFormattedOutputFromValueList( EventSummaryAsValueList( event ) );
}

StumplessFormattedOutput *
StumplessGenericArrayValueAsText( StumplessValue * value )
{
  StumplessValueList * output = GenericArrayValueAsValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessGenericValueAsText( StumplessValue * value )
{
  StumplessValueList * output = GenericValueAsValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * level )
{
  return TextFormattedOutputFromValueList( LevelAsValueList( level ) );
}

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * value )
{
  return TextFormattedOutputFromValueList( ValueAsValueList( value ) );
}

StumplessFormattedOutput *
StumplessValueTypeAsText( StumplessValueType type )
{
  return TextFormattedOutputFromValueList( ValueTypeAsValueList( type ) );
}

static
StumplessValueList *
BooleanArrayValueAsValueList( StumplessValue * value )
{
  return NULL;
}

static
StumplessValueList *
BooleanValueAsValueList( StumplessValue * value )
{
  return NULL;
}

static
StumplessValueList *
EntryAsValueList( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  StumplessValueList * output = EntrySummaryAsValueList( entry );
  if( output == NULL )
    return NULL;
  
  if( entry->attributes != NULL && entry->attribute_count > 0 ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    StumplessValueList * attributes = EntryAttributeListAsValueList( entry );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
StumplessValueList *
EntryAttributeAsValueList( StumplessEntryAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  StumplessEventAttribute * event_attribute = attribute->event_attribute;
  
  const char * attribute_name;
  if( event_attribute == NULL || event_attribute->name == NULL )
    attribute_name = "attribute";
  else
    attribute_name = event_attribute->name;
  
  StumplessStatusCode status;
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, attribute_name ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) );
  
  StumplessValue * attribute_value;
  if( attribute->value != NULL )
    attribute_value = attribute->value;
  else if( event_attribute != NULL && event_attribute->default_value != NULL )
    attribute_value = event_attribute->default_value;
  else
    return NULL;
  
  StumplessValueList * values = ValueAsValueList( attribute_value );
  if( values == NULL )
    return NULL;
  NULL_ON_FAILURE( StumplessAppendValueLists( output, values ) )
  
  return output;
}

static
StumplessValueList *
EntryAttributeListAsValueList( StumplessEntry * entry )
{
  if( entry == NULL || entry->attributes == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  StumplessValueList * attribute;
  unsigned i;
  for( i = 0; i < entry->attribute_count; i++ ){
    attribute = EntryAttributeAsValueList( entry->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !StumplessValueListIsEmpty( output ) )
      NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ", " ) )
    
    NULL_ON_FAILURE ( StumplessAppendValueLists( output, attribute ) )
  }
  
  return output;
}

static
StumplessValueList *
EntrySummaryAsValueList( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  const char * description;
  if( entry->description == NULL )
    description = "entry";
  else
    description = entry->description;
  
  StumplessStatusCode status;
  status = StumplessAppendStringToValueList( output, description );
  NULL_ON_FAILURE( status )
  
  StumplessValueList * event;
  if( entry->event != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, " [" ) )
      
    event = EventSummaryAsValueList( entry->event );
    if( event == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, event ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, "]" ) )
  }
  
  return output;
}

static
StumplessValueList *
EventAsValueList( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessStatusCode status;
  StumplessValueList * output = EventSummaryAsValueList( event );
  if( output == NULL )
    return NULL;
  
  if( event->attributes != NULL && event->attribute_count > 0 ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    StumplessValueList * attributes = EventAttributeListAsValueList( event );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
StumplessValueList *
EventAttributeAsValueList( StumplessEventAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  const char * name;
  if( attribute->name == NULL )
    name = "attribute";
  else
    name = attribute->name;
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, name ) )
  
  if( attribute->default_value != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    StumplessValueList * default_value;
    default_value = ValueAsValueList( attribute->default_value );
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, default_value ) )
  }
  
  return output; 
}

static
StumplessValueList *
EventAttributeListAsValueList( StumplessEvent * event )
{
  if( event == NULL || event->attributes == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  unsigned i;
  StumplessValueList * attribute;
  for( i = 0; i < event->attribute_count; i++ ){
    attribute = EventAttributeAsValueList( event->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !StumplessValueListIsEmpty( output ) )
      NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ", " ) )
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, attribute ) )
  }
  
  return output;
}

static
StumplessValueList *
EventSummaryAsValueList( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  const char * event_name = event->name == NULL ? "event" : event->name;
  StumplessStatusCode status;
  status = StumplessAppendStringToValueList( output, event_name );
  NULL_ON_FAILURE( status );
  
  if( event->level != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, " (" ) )
    
    StumplessValueList * level = LevelAsValueList( event->level );
    if( level == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, level ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  }
  
  return output;
}

static
StumplessValueList *
GenericArrayValueAsValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessCustomProfile * profile;
  profile = StumplessFindProfileByIndex( value->profile );
  if( profile == NULL )
    return NULL;
  
  StumplessValueList * output = profile->value_list_converter( value );
  if( output == NULL )
    return NULL;
  
  StumplessValue * separator = StumplessValueFromString( ", " );
  NULL_ON_FAILURE( StumplessAddSeparatorToValueList( output, separator ) )

  NULL_ON_FAILURE( StumplessPrependStringToValueList( output, "[" ) )
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, "] (" ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, profile->name ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  
  return output;
}

static
StumplessValueList *
GenericValueAsValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  NULL_ON_FAILURE( StumplessAppendValueToValueList( output, value ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, " (" ) )
  
  StumplessCustomProfile * profile;
  profile = StumplessFindProfileByIndex( value->profile );
  if( profile == NULL )
    return NULL;
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, profile->name ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  
  return output;
}

static
StumplessValueList *
LevelAsValueList( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  if( level->name != NULL ){
    status = StumplessAppendStringToValueList( output, level->name );
    NULL_ON_FAILURE( status )
    
    status = StumplessAppendStringToValueList( output, ": " );
    NULL_ON_FAILURE( status )
  }
  
  status = StumplessAppendStringToValueList( output, "level " );
  NULL_ON_FAILURE( status )
  status = StumplessAppendUnsignedIntToValueList( output, level->value );
  NULL_ON_FAILURE( status )
  
  return output;
}

static
StumplessFormattedOutput *
TextFormattedOutputFromValueList( StumplessValueList * list )
{
  if( list == NULL )
    return NULL;
  
  StumplessFormattedOutput * output;
  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  output->payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( output->payload == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  output->payload->values = list;
  
  return output;
}

static
StumplessValueList *
ValueAsValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  if( StumplessValueIsArray( value ) ){
    StumplessValue * separator = StumplessValueFromString( ", " );
    StumplessValueList * array = StumplessArrayValueToValueList( value );
    NULL_ON_FAILURE( StumplessAddSeparatorToValueList( array, separator ) )
    NULL_ON_FAILURE( StumplessPrependStringToValueList( array, "[" ) )
    NULL_ON_FAILURE( StumplessAppendStringToValueList( array, "]" ) )
    NULL_ON_FAILURE( StumplessAppendValueLists( output, array ) )
  } else {
    NULL_ON_FAILURE( StumplessAppendValueToValueList( output, value ) )
  }
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, " (" ) )
  
  StumplessFormattedOutput * type = StumplessValueTypeAsText( value->type );
  if( type == NULL || type->payload == NULL )
    return NULL;
  StumplessValueList * type_values = type->payload->values;
  free( type->payload );
  free( type );
  
  NULL_ON_FAILURE( StumplessAppendValueLists( output, type_values ) )
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  
  return output;
}

static
StumplessValueList *
ValueTypeAsValueList( StumplessValueType type )
{
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  const char * name;
  
  switch( type ){
    case STUMPLESS_UNSIGNED_SHORT:
      name = "unsigned short";
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      name = "unsigned short array";
      break;
    case STUMPLESS_SHORT:
      name = "short";
      break;
    case STUMPLESS_SHORT_POINTER:
      name = "short array";
      break;
    case STUMPLESS_UNSIGNED_INT:
      name = "unsigned int";
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      name = "unsigned int array";
      break;
    case STUMPLESS_INT:
      name = "int";
      break;
    case STUMPLESS_INT_POINTER:
      name = "int array";
      break;
    case STUMPLESS_UNSIGNED_LONG:
      name = "unsigned long";
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      name = "unsigned long";
      break;
    case STUMPLESS_LONG:
      name = "long";
      break;
    case STUMPLESS_LONG_POINTER:
      name = "long array";
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      name = "unsigned long long";
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      name = "unsigned long long array";
      break;
    case STUMPLESS_LONG_LONG:
      name = "long long";
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      name = "long long break";
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      name = "unsigned char";
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      name = "unsigned char array";
      break;
    case STUMPLESS_CHAR:
      name = "char";
      break;
    case STUMPLESS_CHAR_POINTER:
      name = "char array";
      break;
    case STUMPLESS_FLOAT:
      name = "float";
      break;
    case STUMPLESS_FLOAT_POINTER:
      name = "float array";
      break;
    case STUMPLESS_DOUBLE:
      name = "double";
      break;
    case STUMPLESS_DOUBLE_POINTER: 
      name = "double array";
      break;
    case STUMPLESS_LONG_DOUBLE:
      name = "long double";
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      name = "long double array";
      break;
    case STUMPLESS_BOOLEAN:
      name = "boolean";
      break;
    case STUMPLESS_STRING:
      name = "string";
      break;
    case STUMPLESS_STRING_POINTER:
      name = "string array";
      break;
    case STUMPLESS_VOID_POINTER:
      name = "void";
      break;
    default:
      return NULL;
  }
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, name ) )
  
  return output;
}
