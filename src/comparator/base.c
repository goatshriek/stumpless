#include <string.h>

#include "private/comparator/base.h"

short
StringComparatorCompare
( const void *str_1, const void *str_2, Dictionary *options )
{
  return strcmp( str_1, str_2 );
}
