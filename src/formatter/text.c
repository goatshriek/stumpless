#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/formatter/text.h>
#include <stumpless/value.h>
#include <stumpless/value/constructor.h>

#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "private/container/list/value.h"
#include "private/exception/checker.h"
#include "private/output.h"
#include "private/output/profile.h"
#include "private/type.h"

Output *
EventToText
( const Formatter *formatter, const Event *event )
{
  Output *attributes_output, *level_output, *output;
  ValueList *list;

  if( !formatter || !event || !event->name )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, event->name );
  AppendStringToValueList( list, " [" );

  level_output = LevelToText( formatter, event->level );
  if( !level_output || !level_output->data ){
    DestroyOutput( output );
    DestroyValueList( list);
    return NULL;
  }

  AppendValueLists( list, level_output->data );

  AppendStringToValueList( list, "] - " );

  attributes_output = EventAttributesToText( formatter, event->attributes );
  if( !attributes_output || !attributes_output->data ){
    DestroyOutput( output );
    return NULL;
  }
  AppendValueLists( list, attributes_output->data );

  output->data = list;
  return output;
}

Output *
EventAttributesToText
( const Formatter *formatter, const Dictionary *attributes )
{
  DictionaryConstIterator *iterator;
  const EventAttribute *attribute;
  Output *attribute_output, *output;
  ValueList *list;

  if( !formatter )
    return NULL;

  iterator = CBeginDictionary( attributes );
  if( !iterator )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  while( attribute = NextInDictionaryConstIterator( iterator ) ){
    if( !ValueListIsEmpty( list ) )
      AppendStringToValueList( list, ", " );

    attribute_output = EventAttributeToText( formatter, attribute );
    if( attribute_output && attribute_output->data )
      AppendValueLists( list, attribute_output->data );
  }

  DestroyDictionaryConstIterator( iterator );
  output->data = list;
  return output;
}

Output *
EventAttributeToText
( const Formatter *formatter, const EventAttribute *attribute )
{
  Output *output, *value_output;
  ValueList *list;

  if( !formatter || !attribute || !attribute->name )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;

  list = NewValueList();
  if( !list )
    return NULL;

  AppendStringToValueList( list, attribute->name );

  if( attribute->default_value ){
    AppendStringToValueList( list, " [" );
    value_output = ValueToText( formatter, attribute->default_value );
    if( value_output && value_output->data ){
      AppendValueLists( list, value_output->data );
    }
    AppendCharToValueList( list, ']' );
  }

  output->data = list;
  return output;
}

Output *
LevelToText
( const Formatter *formatter, const Level *level )
{
  Output *output;
  ValueList *list;

  if( !formatter || !level || !level->name )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, level->name );
  AppendStringToValueList( list, " (" );
  AppendUnsignedIntToValueList( list, level->primary );
  AppendCharToValueList( list, '.' );
  AppendUnsignedIntToValueList( list, level->secondary );
  AppendCharToValueList( list, '.' );
  AppendUnsignedIntToValueList( list, level->tertiary );
  AppendCharToValueList( list, ')' );

  output->data = list;
  return output;
}

Output *
RecordAttributesToText
( const Formatter *formatter, const Dictionary *attributes )
{
  DictionaryConstIterator *iterator;
  Output *attribute_output, *output;
  const RecordAttribute *attribute;
  ValueList *list;

  if( !formatter )
    return NULL;

  iterator = CBeginDictionary( attributes );
  if( !iterator )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  while( attribute = NextInDictionaryConstIterator( iterator ) ){
    if( !ValueListIsEmpty( list ) )
      AppendStringToValueList( list, ", " );

    attribute_output = RecordAttributeToText( formatter, attribute );
    if( attribute_output && attribute_output->data )
      AppendValueLists( list, attribute_output->data );
  }

  DestroyDictionaryConstIterator( iterator );
  output->data = list;
  return output;
}

Output *
RecordAttributeToText
( const Formatter *formatter, const RecordAttribute *attribute )
{
  Output *output, *value_output;
  ValueList *list;

  if( !formatter || !attribute ||
      ( !attribute->name && !attribute->event_attribute->name ) ||
      ( !attribute->value && !attribute->event_attribute->default_value ) )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, attribute->name );

  AppendStringToValueList( list, ": " );

  value_output = ValueToText( formatter, attribute->value );
  if( !value_output )
    value_output = ValueToText( formatter, attribute->event_attribute->default_value );

  if( value_output && value_output->data ){
    AppendValueLists( list, value_output->data );
  }

  output->data = list;
  return output;
}

Output *
RecordToText
( const Formatter *formatter, const Record *record )
{
  Output *attributes_output, *level_output, *output;
  ValueList *list;

  if( !formatter || !record || !record->event )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, record->event->name );
  AppendStringToValueList( list, " [" );

  level_output = LevelToText( formatter, record->event->level );
  if( !level_output || !level_output->data ){
    DestroyOutput( output );
  }
  AppendValueLists( list, level_output->data );

  AppendStringToValueList( list, "] - " );

  attributes_output = RecordAttributesToText( formatter, record->attributes );
  if( attributes_output && attributes_output->data ){
    AppendValueLists( list, attributes_output->data );
  }

  output->data = list;
  return output;
}

Output *
ValueToText
( const Formatter *formatter, const Value *value )
{
  Output *output;

  if( !formatter || !value || !value->profile || !value->profile->to_value_list )
    return NULL;

  output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;

  output->data = value->profile->to_value_list( value );

  return output;
}
