#include "private/dictionary.h"
#include "private/filter_base.h"
#include "private/type.h"

unsigned short
EmptyFilterAcceptEntry
( Entry * entry, Dictionary * options )
{
  return ( entry != NULL && entry->event != NULL )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptOutput
( Output * output, Dictionary * options )
{
  return ( output != NULL && output->data != NULL )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
EmptyFilterAcceptValue
( Value * value, Dictionary * options )
{
  return ( value != NULL && value->data != NULL )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptEntry
( Entry * entry, Dictionary * options )
{
  return ( entry != NULL && entry->event != NULL
           && entry->event->level != NULL )
       ^ ( GetDictionaryValue( options, "invert" ) != NULL );
}

unsigned short
LevelFilterAcceptOutput
( Output * output, Dictionary * options )
{
  return 1;
}

unsigned short
LevelFilterAcceptValue
( Value * value, Dictionary * options )
{
  return 1;
}
