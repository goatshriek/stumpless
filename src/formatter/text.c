#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/formatter/text.h>

#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "private/container/list/value.h"
#include "private/output.h"
#include "private/output/profile.h"
#include "private/status/checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value/constructor.h"

Output *
EventToText
( const Formatter *formatter, const Event *event )
{
  if( !formatter || !event || !event->name )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data ){
    DestroyOutput( output );
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  ValueList *list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, event->name );
  AppendStringToValueList( list, " [" );

  Output *level_output = LevelToText( formatter, event->level );
  if( !level_output || !level_output->data ){
    DestroyOutput( output );
    DestroyValueList( list);
  }
  AppendValueLists( list, level_output->data->v_p );

  AppendStringToValueList( list, "] - " );

  Output *attributes_output = EventAttributesToText( formatter, event->attributes );
  if( !attributes_output || !attributes_output->data ){
    DestroyOutput( output );
    DestroyValueList( list);
  }
  AppendValueLists( list, attributes_output->data->v_p );

  output->data->v_p = ( void * ) list;
  return output;
}

Output *
EventAttributesToText
( const Formatter *formatter, const Dictionary *attributes )
{
  if( !formatter )
    return NULL;

  DictionaryConstIterator *iterator = CBeginDictionary( attributes );
  if( !iterator )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  output->data = malloc( sizeof( Data ) );
  if( !output->data ){
    DestroyOutput( output );
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  ValueList *list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    DestroyDictionaryConstIterator( iterator );
  }

  const EventAttribute *attribute;
  Output *attribute_output;
  while( attribute = NextInDictionaryConstIterator( iterator ) ){
    if( !ValueListIsEmpty( list ) )
      AppendStringToValueList( list, ", " );

    attribute_output = EventAttributeToText( formatter, attribute );
    if( attribute_output && attribute_output->data )
      AppendValueLists( list, attribute_output->data->v_p );
  }

  DestroyDictionaryConstIterator( iterator );
  output->data->v_p = ( void * ) list;
  return output;
}

Output *
EventAttributeToText
( const Formatter *formatter, const EventAttribute *attribute )
{
  if( !formatter || !attribute || !attribute->name )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;

  ValueList *list = NewValueList();
  if( !list )
    return NULL;

  AppendStringToValueList( list, attribute->name );

  Output *value_output;
  if( attribute->default_value ){
    AppendStringToValueList( list, " [" );
    value_output = ValueToText( formatter, attribute->default_value );
    if( value_output && value_output->data ){
      AppendValueLists( list, value_output->data->v_p );
    }
    AppendCharToValueList( list, ']' );
  }

  output->data->v_p = ( void * ) list;
  return output;
}

Output *
LevelToText
( const Formatter *formatter, const Level *level )
{
  if( !formatter || !level || !level->name )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data ){
    DestroyOutput( output );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  ValueList *list = NewValueList();
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

  output->data->v_p = ( void * ) list;
  return output;
}

Output *
RecordAttributesToText
( const Formatter *formatter, const Dictionary *attributes )
{
  if( !formatter )
    return NULL;

  DictionaryConstIterator *iterator = CBeginDictionary( attributes );
  if( !iterator )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyDictionaryConstIterator( iterator );
    return NULL;
  }

  ValueList *list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    DestroyDictionaryConstIterator( iterator );
  }

  const RecordAttribute *attribute;
  Output *attribute_output;
  while( attribute = NextInDictionaryConstIterator( iterator ) ){
    if( !ValueListIsEmpty( list ) )
      AppendStringToValueList( list, ", " );

    attribute_output = RecordAttributeToText( formatter, attribute );
    if( attribute_output && attribute_output->data )
      AppendValueLists( list, attribute_output->data->v_p );
  }

  DestroyDictionaryConstIterator( iterator );
  output->data = ( void * ) list;
  return output;
}

Output *
RecordAttributeToText
( const Formatter *formatter, const RecordAttribute *attribute )
{
  if( !formatter || !attribute ||
      ( !attribute->name && !attribute->event_attribute->name ) ||
      ( !attribute->value && !attribute->event_attribute->default_value ) )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data ){
    DestroyOutput( output );
    return NULL;
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  ValueList *list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, attribute->name );

  AppendStringToValueList( list, ": " );

  Output *value_output = ValueToText( formatter, attribute->value );
  if( !value_output )
    value_output = ValueToText( formatter, attribute->event_attribute->default_value );

  if( value_output && value_output->data ){
    AppendValueLists( list, value_output->data->v_p );
  }

  output->data->v_p = ( void  * ) list;
  return output;
}

Output *
RecordToText
( const Formatter *formatter, const Record *record )
{
  if( !formatter || !record || !record->event )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data ){
    DestroyOutput( output );
  }

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile ){
    DestroyOutput( output );
    return NULL;
  }

  ValueList *list = NewValueList();
  if( !list ){
    DestroyOutput( output );
    return NULL;
  }

  AppendStringToValueList( list, record->event->name );
  AppendStringToValueList( list, " [" );

  Output *level_output = LevelToText( formatter, record->event->level );
  if( !level_output || !level_output->data ){
    DestroyOutput( output );
    DestroyValueList( list);
  }
  AppendValueLists( list, level_output->data->v_p );

  AppendStringToValueList( list, "] - " );

  Output *attributes_output = RecordAttributesToText( formatter, record->attributes );
  if( !attributes_output || !attributes_output->data ){
    DestroyOutput( output );
    DestroyValueList( list);
  }
  AppendValueLists( list, attributes_output->data->v_p );

  output->data->v_p = ( void * ) list;
  return output;
}

Output *
ValueToText
( const Formatter *formatter, const Value *value )
{
  if( !formatter || !value || !value->profile || !value->profile->to_value_list )
    return NULL;

  Output *output = malloc( sizeof( Output ) );
  if( !output )
    return NULL;

  output->data = malloc( sizeof( Data ) );
  if( !output->data )
    return NULL;

  output->profile = FindOutputProfileByName( "text" );
  if( !output->profile )
    return NULL;

  output->data->v_p = ( void * ) value->profile->to_value_list( value );

  return output;
}
