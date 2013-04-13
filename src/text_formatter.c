#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <formatted_output.h>
#include <status.h>
#include <text_formatter.h>
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
  if( entry->attribute_count > 0 && entry->attributes != NULL ){
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
  
  if( event->attribute_count > 0 ){
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
  
  if( attribute->name == NULL )
    status = StumplessAppendStringToFormattedOutput( output, "attribute" );
  else
    status = StumplessAppendStringToFormattedOutput( output, attribute->name );
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
  
  unsigned int i = 0;
  StumplessFormattedOutput * attribute_output;
  StumplessStatusCode status;
  while( i < event->attribute_count ){
    attribute_output = StumplessEventAttributeAsText( event->attributes[i] );
    status = StumplessAppendFormattedOutputs( output, attribute_output );
    NULL_ON_FAILURE( status )
    
    if( ++i < event->attribute_count )
      NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ", " ) )
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
  
  StumplessStatusCode status;
  
  if( event->name == NULL ){
    if( event->level == NULL ){
      status = StumplessAppendStringToFormattedOutput( output, "event" );
      NULL_ON_FAILURE( status )
    } else {
      output = StumplessLevelAsText( event->level );
      status = StumplessAppendStringToFormattedOutput( output, " event" );
      NULL_ON_FAILURE( status )
    }
  } else {
    status = StumplessAppendStringToFormattedOutput( output, event->name );
    NULL_ON_FAILURE( status )
    
    if( event->level != NULL ) {
      NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, " (" ) )
      
      StumplessFormattedOutput * level_output;
      level_output = StumplessLevelAsText( event->level );
      NULL_ON_FAILURE( StumplessAppendFormattedOutputs( output, level_output ) )
      
      NULL_ON_FAILURE( StumplessAppendStringToFormattedOutput( output, ")" ) )
    }
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
  // todo add the type of the value to this output
  
  if( value == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  StumplessValueList * list = output->payload->values;
  NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value ) )
  
  return output;
}
