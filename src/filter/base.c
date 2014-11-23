#include "private/container/dictionary.h"
#include "private/filter/base.h"
#include "private/type.h"

unsigned short
EmptyFilterAcceptRecord
( const Filter *filter, const Record *record )
{
  if( !filter )
    return 1;

  return ( record  && record->event )
       ^ ( GetDictionaryValue( filter->options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptOutput
(const Filter *filter, const Output *output )
{
  if( !filter )
    return 1;

  return ( output && output->data )
       ^ ( GetDictionaryValue( filter->options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptValue
( const Filter *filter, const Value *value )
{
  if( !filter )
    return 1;

  return ( value != NULL )
       ^ ( GetDictionaryValue( filter->options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptRecord
( const Filter *filter, const Record *record )
{
  if( !filter )
    return 1;

  return ( record && record->event && record->event->level )
       ^ ( GetDictionaryValue( filter->options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptOutput
( const Filter *filter, const Output *output )
{
  return 1;
}

unsigned short
LevelFilterAcceptValue
( const Filter *filter, const Value *value )
{
  return 1;
}
