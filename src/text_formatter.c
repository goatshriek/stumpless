#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/output.h"
#include "private/output_profile.h"
#include "private/status_checker.h"
#include "private/text_formatter.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"

#include "private/list/entry_attribute.h"
#include "private/list/event_attribute.h"
#include "private/list/value.h"

#include "private/list/iterator/entry_attribute.h"
#include "private/list/iterator/event_attribute.h"

#include "static/text_formatter.h"

Output *
ArrayValueToText
( const Value * value )
{
  ValueList * output = ArrayValueToValueList( value );
  return TextOutputFromValueList( output );
}

Output *
EntryToText
( const Entry * entry, Dictionary * options )
{
  return TextOutputFromValueList( EntryToValueList( entry ) );
}

Output *
EntryAttributeToText
( const EntryAttribute * attribute )
{
  ValueList * output = EntryAttributeToValueList( attribute );
  return TextOutputFromValueList( output );
}

Output *
EntryAttributeListToText
( const Entry * entry )
{
  ValueList * output = EntryAttributeListToValueList( entry );
  return TextOutputFromValueList( output );
}

Output *
EntrySummaryToText
( const Entry * entry )
{
  return TextOutputFromValueList( EntrySummaryToValueList( entry ) );
}

Output *
EventToText
( const Event * event )
{
  return TextOutputFromValueList( EventToValueList( event ) );
}

Output *
EventAttributeToText
( const EventAttribute * attribute )
{
  ValueList * output = EventAttributeToValueList( attribute );
  return TextOutputFromValueList( output );
}

Output *
EventAttributeListToText
( const Event * event )
{
  ValueList * output = EventAttributeListToValueList( event );
  return TextOutputFromValueList( output );
}

Output *
EventSummaryToText
( const Event * event )
{
  return TextOutputFromValueList( EventSummaryToValueList( event ) );
}

Output *
LevelToText
( const Level * level )
{
  return TextOutputFromValueList( LevelToValueList( level ) );
}

Output *
SingularValueToText
( const Value * value )
{
  ValueList * output = SingularValueToValueList( value );
  return TextOutputFromValueList( output );
}

static
ValueList *
ArrayValueToValueList
( const Value *value )
{
  if( !value )
    return NULL;
  
  ValueProfile *profile = value->profile;
  if( !profile )
    return NULL;
  
  ValueList *output = profile->to_value_list( value );
  if( !output )
    return NULL;
  
  Value *separator = ValueFromString( ", " );
  if( !AddSeparatorToValueList( output, separator ) )
    return NULL;

  if( !PrependStringToValueList( output, "[" ) )
    return NULL;

  if( !AppendStringToValueList( output, "] (" ) )
    return NULL;
  
  if( !AppendStringToValueList( output, profile->name ) )
    return NULL;
  
  if( AppendStringToValueList( output, ")" ) )
    return NULL;
  
  return output;
}

static
ValueList *
EntryToValueList
( const Entry *entry )
{
  if( !entry )
    return NULL;
  
  ValueList *output = EntrySummaryToValueList( entry );
  if( !output )
    return NULL;
  
  if( !EntryAttributeListIsEmpty( entry->attributes ) ){
    if( !AppendStringToValueList( output, ": " ) )
      return NULL;
    
    ValueList *attributes = EntryAttributeListToValueList( entry );
    if( !attributes )
      return NULL;
    
    if( !AppendValueLists( output, attributes ) )
      return NULL;
  }
  
  return output;
}

static
ValueList *
EntryAttributeToValueList
( const EntryAttribute *attribute )
{
  if( !attribute )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  EventAttribute *event_attribute = attribute->event_attribute;
  
  const char *attribute_name;
  if( !event_attribute || !event_attribute->name )
    attribute_name = "attribute";
  else
    attribute_name = event_attribute->name;
  
  if( !AppendStringToValueList( output, attribute_name ) )
    return NULL;
  
  if( !AppendStringToValueList( output, ": " ) )
    return NULL;
  
  Value * attribute_value;
  if( attribute->value )
    attribute_value = attribute->value;
  else if( event_attribute && event_attribute->default_value )
    attribute_value = event_attribute->default_value;
  else
    return NULL;
  
  if( !attribute_value->profile )
    return NULL;
  
  Output * value_as_text;
  value_as_text = attribute_value->profile->to_text( attribute_value );
  if( !value_as_text )
    return NULL;
  
  ValueList * values = ( ValueList * ) value_as_text->data->v_p;
  if( !AppendValueLists( output, values ) )
    return NULL;
  
  return output;
}

static
ValueList *
EntryAttributeListToValueList
( const Entry *entry )
{
  if( !entry || EntryAttributeListIsEmpty( entry->attributes ) )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  ValueList *attribute_list;
  EntryAttribute *attribute;
  EntryAttributeListIterator *iterator = BeginEntryAttributeList( entry->attributes );
  while( attribute = NextInEntryAttributeListIterator( iterator ) ){
    attribute_list = EntryAttributeToValueList( attribute );
    if( !attribute_list )
      continue;
    
    if( !ValueListIsEmpty( output ) )
      if( !AppendStringToValueList( output, ", " ) )
        return NULL;
    
    if( !AppendValueLists( output, attribute_list ) )
      return NULL;
  }
  
  DestroyEntryAttributeListIterator( iterator );
  return output;
}

static
ValueList *
EntrySummaryToValueList
( const Entry *entry )
{
  if( !entry )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  const char *description;
  if( !entry->description )
    description = "entry";
  else
    description = entry->description;
  
  if( !AppendStringToValueList( output, description ) )
    return NULL;
  
  ValueList *event;
  if( entry->event ){
    if( !AppendStringToValueList( output, " [" ) )
      return NULL;
      
    event = EventSummaryToValueList( entry->event );
    if( !event )
      return NULL;
    
    if( !AppendValueLists( output, event ) )
      return NULL;
    
    if( !AppendStringToValueList( output, "]" ) )
      return NULL;
  }
  
  return output;
}

static
ValueList *
EventToValueList
( const Event *event )
{
  if( !event )
    return NULL;
  
  ValueList *output = EventSummaryToValueList( event );
  if( !output )
    return NULL;
  
  if( !EventAttributeListIsEmpty( event->attributes ) ){
    if( !AppendStringToValueList( output, ": " ) )
      return NULL;
    
    ValueList *attributes = EventAttributeListToValueList( event );
    if( !attributes )
      return NULL;
    
    if( !AppendValueLists( output, attributes ) )
      return NULL;
  }
  
  return output;
}

static
ValueList *
EventAttributeToValueList
( const EventAttribute *attribute )
{
  if( !attribute )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  const char *name;
  if( attribute->name )
    name = attribute->name;
  else
    name = "attribute";
  if( !AppendStringToValueList( output, name ) )
    return NULL;
  
  Value *default_value = attribute->default_value;
  if( default_value ){
    if( !AppendStringToValueList( output, ": " ) )
      return NULL;
    
    if( !default_value->profile )
      return NULL;
    
    Output *default_value_output;
    default_value_output = default_value->profile->to_text( default_value );
    
    ValueList *default_value_list;
    default_value_list = ( ValueList * ) default_value_output->data->v_p;
    
    if( !AppendValueLists( output, default_value_list ) )
      return NULL;
  }
  
  return output; 
}

static
ValueList *
EventAttributeListToValueList
( const Event *event )
{
  if( !event || !event->attributes )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  ValueList *attribute_list;
  EventAttribute *attribute;
  EventAttributeListIterator *attributes = BeginEventAttributeList( event->attributes );
  while( attribute = NextInEventAttributeListIterator( attributes ) ){
    attribute_list = EventAttributeToValueList( attribute );
    if( !attribute_list )
      continue;
    
    if( !ValueListIsEmpty( output ) ){
      if( !AppendStringToValueList( output, ", " ) ){
        return NULL;
      }
    }
    
    if( !AppendValueLists( output, attribute_list ) )
      return NULL;
  }
  
  DestroyEventAttributeListIterator( attributes );
  return output;
}

static
ValueList *
EventSummaryToValueList
( const Event *event )
{
  if( !event )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  const char *event_name = event->name ? event->name : "event";
  if( !AppendStringToValueList( output, event_name ) )
    return NULL;
  
  if( event->level ){
    if( !AppendStringToValueList( output, " (" ) )
      return NULL;
    
    ValueList * level = LevelToValueList( event->level );
    if( !level )
      return NULL;
    
    if( !AppendValueLists( output, level ) )
      return NULL;
    
    if( !AppendStringToValueList( output, ")" ) )
      return NULL;
  }
  
  return output;
}

static
ValueList *
LevelToValueList
( const Level *level )
{
  if( !level )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  if( level->name ){
    if( !AppendStringToValueList( output, level->name ) )
      return NULL;
    
    if( !AppendStringToValueList( output, ": " ) )
      return NULL;
  }
  
  if( !AppendStringToValueList( output, "level " ) )
    return NULL;
  
  return AppendUnsignedIntToValueList( output, level->value );
}

static
ValueList *
SingularValueToValueList
( const Value *value )
{
  if( !value )
    return NULL;
  
  ValueProfile *profile;
  profile = value->profile;
  if( !profile )
    return NULL;
  
  ValueList *output = NewValueList();
  if( !output )
    return NULL;
  
  if( !AppendToValueList( output, CopyValue( value ) ) )
    return NULL;
  
  if( !AppendStringToValueList( output, " (" ) )
    return NULL;

  if( !AppendStringToValueList( output, profile->name ) )
    return NULL;
  
  if( !AppendStringToValueList( output, ")" ) )
    return NULL;
  
  return output;
}

static
Output *
TextOutputFromValueList
( const ValueList *list )
{
  if( !list )
    return NULL;
  
  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;
  
  output->data = malloc( sizeof( Type ) );
  if( !output->data )
    return NULL;
  
  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;
  
  output->data->v_p = ( void * ) ValueListToStrings( list );
  
  return output;
}
