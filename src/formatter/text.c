#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "private/container/list/value.h"
#include "private/formatter/text.h"
#include "private/output.h"
#include "private/output/profile.h"
#include "private/status/checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value/constructor.h"
#include "static/formatter/text.h"

Output *
ArrayValueToText
( const Value * value )
{
  ValueList * output = ArrayValueToValueList( value );
  return TextOutputFromValueList( output );
}

Output *
RecordToText
( const Formatter *formatter, const Record * record )
{
  return TextOutputFromValueList( RecordToValueList( record ) );
}

Output *
RecordAttributeToText
( const RecordAttribute * attribute )
{
  ValueList * output = RecordAttributeToValueList( attribute );
  return TextOutputFromValueList( output );
}

Output *
RecordAttributeListToText
( const Record * record )
{
  ValueList * output = RecordAttributeListToValueList( record );
  return TextOutputFromValueList( output );
}

Output *
RecordSummaryToText
( const Record * record )
{
  return TextOutputFromValueList( RecordSummaryToValueList( record ) );
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
( const Event *event )
{
  ValueList *output = EventAttributeListToValueList( event );
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

  Value *separator = NewValueForString( ", " );
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
RecordToValueList
( const Record *record )
{
  if( !record )
    return NULL;

  ValueList *output = RecordSummaryToValueList( record );
  if( !output )
    return NULL;

  if( !DictionaryIsEmpty( record->attributes ) ){
    if( !AppendStringToValueList( output, ": " ) )
      return NULL;

    ValueList *attributes = RecordAttributeListToValueList( record );
    if( !attributes )
      return NULL;

    if( !AppendValueLists( output, attributes ) )
      return NULL;
  }

  return output;
}

static
ValueList *
RecordAttributeToValueList
( const RecordAttribute *attribute )
{
  if( !attribute )
    return NULL;

  ValueList *output = NewValueList();
  if( !output )
    return NULL;

  const EventAttribute *event_attribute = attribute->event_attribute;

  const char *attribute_name;
  if( !event_attribute || !event_attribute->name )
    attribute_name = "attribute";
  else
    attribute_name = event_attribute->name;

  if( !AppendStringToValueList( output, attribute_name ) )
    return NULL;

  if( !AppendStringToValueList( output, ": " ) )
    return NULL;

  Value *attribute_value;
  if( attribute->value )
    attribute_value = attribute->value;
  else if( event_attribute && event_attribute->default_value )
    attribute_value = event_attribute->default_value;
  else
    return NULL;

  if( !attribute_value->profile )
    return NULL;

  Output *value_as_text;
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
RecordAttributeListToValueList
( const Record *record )
{
  if( !record || DictionaryIsEmpty( record->attributes ) )
    return NULL;

  ValueList *output = NewValueList();
  if( !output )
    return NULL;

  ValueList *attribute_list;
  const RecordAttribute *attribute;
  DictionaryConstIterator *iterator = CBeginDictionary( record->attributes );
  while( attribute = NextInDictionaryConstIterator( iterator ) ){
    attribute_list = RecordAttributeToValueList( attribute );
    if( !attribute_list )
      continue;

    if( !ValueListIsEmpty( output ) )
      if( !AppendStringToValueList( output, ", " ) )
        return NULL;

    if( !AppendValueLists( output, attribute_list ) )
      return NULL;
  }

  DestroyDictionaryConstIterator( iterator );
  return output;
}

static
ValueList *
RecordSummaryToValueList
( const Record *record )
{
  if( !record )
    return NULL;

  ValueList *output = NewValueList();
  if( !output )
    return NULL;

  ValueList *event;
  if( record->event ){
    if( !AppendStringToValueList( output, " [" ) )
      return NULL;

    event = EventSummaryToValueList( record->event );
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

  if( !DictionaryIsEmpty( event->attributes ) ){
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
  const EventAttribute *attribute;
  DictionaryConstIterator *attributes = CBeginDictionary( event->attributes );
  while( attribute = NextInDictionaryConstIterator( attributes ) ){
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

  DestroyDictionaryConstIterator( attributes );
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

  return AppendUnsignedIntToValueList( output, level->primary );
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
