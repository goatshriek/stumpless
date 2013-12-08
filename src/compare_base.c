#include <string.h>

#include "private/compare_base.h"

short
CompareStrings
( const void * str_1, const void * str_2, Dictionary * options )
{ 
  return strcmp( str_1, str_2 );
}

short
CompareStringValues
( const void * value_1, const void * value_2, Dictionary * options )
{
  return 0;
}
