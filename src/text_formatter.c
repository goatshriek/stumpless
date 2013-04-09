#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <formatted_output.h>
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
  
  // todo need to implement
  
  return NULL;
}

StumplessFormattedOutput *
StumplessEntryAttributeAsText( StumplessEntryAttribute * attribute )
{
  // todo need to implement
  
  return NULL;
}

StumplessFormattedOutput *
StumplessEntryAttributeListAsText( StumplessEntry * entry )
{
  return NULL;
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
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    
    StumplessFormattedOutput * attribute_output;
    attribute_output = StumplessEventAttributeListAsText( event );
    status = StumplessAppendFormattedOutputs( output, attribute_output );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
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
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  if( attribute->default_value != NULL ){
    status = StumplessAppendStringToFormattedOutput( output, ": " );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    
    status = StumplessAppendValueToFormattedOutput( output,
                                                    attribute->default_value );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
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
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    
    if( ++i < event->attribute_count ){
      status = StumplessAppendStringToFormattedOutput( output, ", " );
      if( status != STUMPLESS_SUCCESS )
        return NULL;
    }
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
      if( status != STUMPLESS_SUCCESS )
        return NULL;
    } else {
      output = StumplessLevelAsText( event->level );
      status = StumplessAppendStringToFormattedOutput( output, " event" );
      if( status != STUMPLESS_SUCCESS )
        return NULL;
    }
  } else {
    status = StumplessAppendStringToFormattedOutput( output, event->name );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    if( event->level != NULL ) {
      status = StumplessAppendStringToFormattedOutput( output, " (" );
      if( status != STUMPLESS_SUCCESS )
        return NULL;
      
      StumplessFormattedOutput * level_output;
      level_output = StumplessLevelAsText( event->level );
      status = StumplessAppendFormattedOutputs( output, level_output );
      if( status != STUMPLESS_SUCCESS )
        return NULL;
      
      status = StumplessAppendStringToFormattedOutput( output, ")" );
      if( status != STUMPLESS_SUCCESS )
        return NULL;
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
    if( status != STUMPLESS_SUCCESS )
      return NULL;
    
    status = StumplessAppendStringToFormattedOutput( output, ": " );
    if( status != STUMPLESS_SUCCESS )
      return NULL;
  }
  
  status = StumplessAppendStringToFormattedOutput( output, "level " );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  status = StumplessAppendUnsignedIntToFormattedOutput( output, level->value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
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
  StumplessStatusCode status = StumplessAppendValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  return output;
}
