#include "private/container/dictionary.h"
#include "private/filter/base.h"
#include "private/type.h"

unsigned short
EmptyFilterAcceptRecord
( const Record *record, Dictionary *options )
{
  return ( record  && record->event )
         ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptOutput
( const Output *output, Dictionary *options )
{
  return ( output && output->data )
         ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptValue
( const Value *value, Dictionary *options )
{
  return ( value && value->data )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptRecord
( const Record *record, Dictionary *options )
{
  return ( record && record->event && record->event->level )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptOutput
( const Output *output, Dictionary *options )
{
  return 1;
}

unsigned short
LevelFilterAcceptValue
( const Value *value, Dictionary *options )
{
  return 1;
}
