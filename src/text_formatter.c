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
StumplessEntryToText( StumplessEntry * entry )
{
  return TextFormattedOutputFromValueList( EntryToValueList( entry ) );
}

StumplessFormattedOutput *
StumplessEntryAttributeToText( StumplessEntryAttribute * attribute )
{
  StumplessValueList * output = EntryAttributeToValueList( attribute );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEntryAttributeListToText( StumplessEntry * entry )
{
  StumplessValueList * output = EntryAttributeListToValueList( entry );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEntrySummaryToText( StumplessEntry * entry )
{
  return TextFormattedOutputFromValueList( EntrySummaryToValueList( entry ) );
}

StumplessFormattedOutput *
StumplessEventToText( StumplessEvent * event )
{
  return TextFormattedOutputFromValueList( EventToValueList( event ) );
}

StumplessFormattedOutput *
StumplessEventAttributeToText( StumplessEventAttribute * attribute )
{
  StumplessValueList * output = EventAttributeToValueList( attribute );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEventAttributeListToText( StumplessEvent * event )
{
  StumplessValueList * output = EventAttributeListToValueList( event );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessEventSummaryToText( StumplessEvent * event )
{
  return TextFormattedOutputFromValueList( EventSummaryToValueList( event ) );
}

StumplessFormattedOutput *
StumplessGenericArrayValueToText( StumplessValue * value )
{
  StumplessValueList * output = GenericArrayValueToValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessGenericValueToText( StumplessValue * value )
{
  StumplessValueList * output = GenericValueToValueList( value );
  return TextFormattedOutputFromValueList( output );
}

StumplessFormattedOutput *
StumplessLevelToText( StumplessLevel * level )
{
  return TextFormattedOutputFromValueList( LevelToValueList( level ) );
}

static
StumplessValueList *
EntryToValueList( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  StumplessValueList * output = EntrySummaryToValueList( entry );
  if( output == NULL )
    return NULL;
  
  if( entry->attributes != NULL && entry->attribute_count > 0 ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    StumplessValueList * attributes = EntryAttributeListToValueList( entry );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
StumplessValueList *
EntryAttributeToValueList( StumplessEntryAttribute * attribute )
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
  
  if( attribute_value->profile == NULL )
    return NULL;
  
  StumplessFormattedOutput * value_as_text;
  value_as_text  = attribute_value->profile->to_text( attribute_value );
  if( value_as_text == NULL )
    return NULL;
  
  StumplessValueList * values = value_as_text->payload->values;
  NULL_ON_FAILURE( StumplessAppendValueLists( output, values ) )
  
  return output;
}

static
StumplessValueList *
EntryAttributeListToValueList( StumplessEntry * entry )
{
  if( entry == NULL || entry->attributes == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  StumplessValueList * attribute;
  unsigned i;
  for( i = 0; i < entry->attribute_count; i++ ){
    attribute = EntryAttributeToValueList( entry->attributes[i] );
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
EntrySummaryToValueList( StumplessEntry * entry )
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
      
    event = EventSummaryToValueList( entry->event );
    if( event == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, event ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, "]" ) )
  }
  
  return output;
}

static
StumplessValueList *
EventToValueList( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessStatusCode status;
  StumplessValueList * output = EventSummaryToValueList( event );
  if( output == NULL )
    return NULL;
  
  if( event->attributes != NULL && event->attribute_count > 0 ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    StumplessValueList * attributes = EventAttributeListToValueList( event );
    if( attributes == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, attributes ) )
  }
  
  return output;
}

static
StumplessValueList *
EventAttributeToValueList( StumplessEventAttribute * attribute )
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
  
  StumplessValue * default_value = attribute->default_value;
  if( default_value != NULL ){
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ": " ) )
    
    if( default_value->profile == NULL )
      return NULL;
    
    StumplessFormattedOutput * default_value_output;
    default_value_output = default_value->profile->to_text( default_value );
    
    StumplessValueList * default_value_list;
    default_value_list = default_value_output->payload->values;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, default_value_list ) )
  }
  
  return output; 
}

static
StumplessValueList *
EventAttributeListToValueList( StumplessEvent * event )
{
  if( event == NULL || event->attributes == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  unsigned i;
  StumplessValueList * attribute;
  for( i = 0; i < event->attribute_count; i++ ){
    attribute = EventAttributeToValueList( event->attributes[i] );
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
EventSummaryToValueList( StumplessEvent * event )
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
    
    StumplessValueList * level = LevelToValueList( event->level );
    if( level == NULL )
      return NULL;
    
    NULL_ON_FAILURE( StumplessAppendValueLists( output, level ) )
    
    NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  }
  
  return output;
}

static
StumplessValueList *
GenericArrayValueToValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueProfile * profile = value->profile;
  if( profile == NULL )
    return NULL;
  
  StumplessValueList * output = profile->to_value_list( value );
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
GenericValueToValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueProfile * profile;
  profile = value->profile;
  if( profile == NULL )
    return NULL;
  
  StumplessValueList * output = StumplessNewValueList();
  if( output == NULL )
    return NULL;
  
  NULL_ON_FAILURE( StumplessAppendValueToValueList( output, value ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, " (" ) )

  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, profile->name ) )
  
  NULL_ON_FAILURE( StumplessAppendStringToValueList( output, ")" ) )
  
  return output;
}

static
StumplessValueList *
LevelToValueList( StumplessLevel * level )
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
  
  output->profile = StumplessFindOutputProfileByName( "Text" );
  if( output->profile == NULL )
    return NULL;
  
  output->payload->values = StumplessValueListToStrings( list );
  
  return output;
}
