#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <formatted_output.h>
#include <status_checker.h>
#include <text_formatter.h>
#include <type.h>
#include <value.h>
#include <value_constructor.h>
#include <value_list.h>

static
StumplessFormattedOutput *
GetTextFormattedOutput( void ){
  StumplessFormattedOutput * output;
  StumplessFormattedPayload * payload;

  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( payload == NULL )
    return NULL;
  
  payload->values = StumplessNewValueList();
  if( payload->values == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  output->payload = payload;
  
  return output;
}

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = StumplessEntrySummaryAsText( entry );
  if( output == NULL )
    return NULL;
  
  StumplessFormattedOutput * attributes;
  if( entry->attributes != NULL && entry->attribute_count > 0 ){
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ": " ) )
    
    attributes = StumplessEntryAttributeListAsText( entry );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendFormattedOutputs( output, attributes ) )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEntryAttributeAsText( StumplessEntryAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessEventAttribute * event_attribute = attribute->event_attribute;
  StumplessValue * attribute_value;
  if( attribute->value != NULL )
    attribute_value = attribute->value;
  else if( event_attribute != NULL && event_attribute->default_value != NULL )
    attribute_value = event_attribute->default_value;
  else
    return NULL;
  
  const char * attribute_name;
  if( event_attribute == NULL || event_attribute->name == NULL )
    attribute_name = "attribute";
  else
    attribute_name = event_attribute->name;
  
  StumplessStatusCode status;
  status = StumplessAppendStringToFormattedOutput( output, attribute_name );
  NULL_ON_FAILURE( status )
  
  NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ": " ) );
  
  status = StumplessAppendValueToFormattedOutput( output, attribute_value );
  NULL_ON_FAILURE( status )
  
  return output;
}

StumplessFormattedOutput *
StumplessEntryAttributeListAsText( StumplessEntry * entry )
{
  if( entry == NULL || entry->attributes == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessFormattedOutput * attribute;
  unsigned i;
  for( i = 0; i < entry->attribute_count; i++ ){
    attribute = StumplessEntryAttributeAsText( entry->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !StumplessFormattedOutputIsEmpty( output ) )
      NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ", " ) )
    
    NULL_ON_FAILURE ( StumplessAppendFormattedOutputs( output, attribute ) )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEntrySummaryAsText( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  const char * description;
  if( entry->description == NULL )
    description = "entry";
  else
    description = entry->description;
  
  StumplessStatusCode status;
  status = StumplessAppendStringToFormattedOutput( output, description );
  NULL_ON_FAILURE( status )
  
  StumplessFormattedOutput * event;
  if( entry->event != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, " [" ) )
      
    event = StumplessEventSummaryAsText( entry->event );
    NULL_ON_FAILURE( StumplessAppendFormattedOutputs( output, event ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, "]" ) )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessStatusCode status;
  StumplessFormattedOutput * output = StumplessEventSummaryAsText( event );
  if( output == NULL )
    return NULL;
  
  if( event->attributes != NULL && event->attribute_count > 0 ){
    status = StumplessAppendStringToFormattedOutput( output, ": " );
    NULL_ON_FAILURE( status )
    
    StumplessFormattedOutput * attribute_output;
    attribute_output = StumplessEventAttributeListAsText( event );
    status = StumplessAppendFormattedOutputs( output, attribute_output );
    NULL_ON_FAILURE( status )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEventAttributeAsText( StumplessEventAttribute * attribute )
{
  if( attribute == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  const char * name;
  if( attribute->name == NULL )
    name = "attribute";
  else
    name = attribute->name;
  status = StumplessAppendStringToFormattedOutput( output, name );
  NULL_ON_FAILURE( status )
  
  if( attribute->default_value != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ": " ) )
    
    status = StumplessAppendValueToFormattedOutput( output,
                                                    attribute->default_value );
    NULL_ON_FAILURE( status )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEventAttributeListAsText( StumplessEvent * event )
{
  if( event == NULL || event->attributes == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  unsigned i;
  StumplessFormattedOutput * attribute;
  StumplessStatusCode status;
  for( i = 0; i < event->attribute_count; i++ ){
    attribute = StumplessEventAttributeAsText( event->attributes[i] );
    if( attribute == NULL )
      continue;
    
    if( !StumplessFormattedOutputIsEmpty( output ) )
      NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ", " ) )
    
    NULL_ON_FAILURE( StumplessAppendFormattedOutputs( output, attribute ) )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessEventSummaryAsText( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  const char * event_name = event->name == NULL ? "event" : event->name;
  StumplessStatusCode status;
  status = StumplessAppendStringToFormattedOutput( output, event_name );
  NULL_ON_FAILURE( status );
  
  if( event->level != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, " (" ) )
    
    StumplessFormattedOutput * level_output;  
    level_output = StumplessLevelAsText( event->level );
    NULL_ON_FAILURE( StumplessAppendFormattedOutputs( output, level_output ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ")" ) )
  }
  
  return output;
}

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
 
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  if( level->name != NULL ){
    status = StumplessAppendStringToFormattedOutput( output, level->name );
    NULL_ON_FAILURE( status )
    
    status = StumplessAppendStringToFormattedOutput( output, ": " );
    NULL_ON_FAILURE( status )
  }
  
  status = StumplessAppendStringToFormattedOutput( output, "level " );
  NULL_ON_FAILURE( status )
  status = StumplessAppendUnsignedIntToFormattedOutput( output, level->value );
  NULL_ON_FAILURE( status )
  
  return output;
}

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessValueList * list = output->payload->values;
  StumplessValue * separator;
  StumplessValueList * array;
  if( StumplessValueIsArray( value ) ){
    separator = StumplessValueFromString( ", " );
    array = StumplessArrayValueToValueList( value );
    NULL_ON_FAILURE( StumplessAddSeparatorToValueList( array, separator ) )
    NULL_ON_FAILURE( StumplessPrependStringToValueList( array, "[" ) )
    NULL_ON_FAILURE( StumplessAppendStringToValueList( array, "]" ) )
    NULL_ON_FAILURE( StumplessAppendValueLists( list, array ) )
  } else {
    NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value ) )
  }
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( list, " (" ) )
  StumplessValueType type = value->type;
  StumplessAppendFormattedOutputs( output, StumplessValueTypeAsText( type ) );
  NULL_ON_FAILURE( StumplessAppendStringToValueList( list, ")" ) )
  
  return output;
}

StumplessFormattedOutput *
StumplessValueTypeAsText( StumplessValueType type )
{
  StumplessFormattedOutput * output = GetTextFormattedOutput();
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
    case STUMPLESS_VOID_POINTER:
      name = "void";
      break;
    default:
      return NULL;
  }
  
  NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, name ) )
  
  return output;
}
