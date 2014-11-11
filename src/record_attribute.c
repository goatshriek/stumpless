#include <stumpless/record_attribute.h>

#include "private/container/dictionary.h"
#include "private/type.h"

static Dictionary *attributes = NULL; /**< all currently defined RecordAttributes */

void
DestroyRecordAttribute
( RecordAttribute *attribute )
{
  if( !attribute )
    return;

  if( attributes )
    RemoveDictionaryValue( attributes, attribute->name );

  free( attribute );
  
  return;
}

RecordAttribute *
NewRecordAttribute
( const char *name )
{
  if( !name )
    return NULL;

  if( !attributes ){
    attributes = NewDictionary();
    if( !attributes )
      return NULL;
  }

  RecordAttribute *attribute = GetDictionaryValue( attributes, name );
  if( attribute )
    return attribute;
  
  attribute = malloc( sizeof( RecordAttribute ) );
  if( !attribute )
    return NULL;

  attribute->name = name;
  
  SetDictionaryValue( attributes, name, attribute );
  
  return attribute;
}

Dictionary *
NewRecordAttributeDictionaryForEventAttributeDictionary
( const Dictionary *event_attributes )
{
  if( !event_attributes )
    return NULL;
  
  Dictionary *record_attributes = NewDictionary();
  if( !record_attributes )
    return NULL;

  

  return record_attributes;
}

RecordAttribute *
NewRecordAttributeForEventAttribute
( const EventAttribute *event_attribute )
{
  if( !event_attribute || !event_attribute->name )
    return NULL;

  if( !attributes ){
    attributes = NewDictionary();
    if( !attributes )
      return NULL;
  }

  RecordAttribute *record_attribute = malloc( sizeof( RecordAttribute ) );
  if( !record_attribute )
    return NULL;

  record_attribute->name = event_attribute->name;
  record_attribute->event_attribute = event_attribute;
  record_attribute->value = event_attribute->default_value;
  
  SetDictionaryValue( attributes, event_attribute->name, record_attribute );
  
  return record_attribute;
}
