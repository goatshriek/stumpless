#include "private/container/dictionary.h"
#include "private/filter_base.h"
#include "private/type.h"

unsigned short
EmptyFilterAcceptEntry
( const Entry * entry, Dictionary * options )
{
  return ( entry  && entry->event )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptOutput
( const Output * output, Dictionary * options )
{
  return ( output && output->data )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptValue
( const Value * value, Dictionary * options )
{
  return ( value && value->data )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptEntry
( const Entry * entry, Dictionary * options )
{
  return ( entry && entry->event && entry->event->level )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptOutput
( const Output * output, Dictionary * options )
{
  return 1;
}

unsigned short
LevelFilterAcceptValue
( const Value * value, Dictionary * options )
{
  return 1;
}
