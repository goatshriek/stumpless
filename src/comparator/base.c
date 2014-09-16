#include <string.h>

#include "private/comparator/base.h"

short
StringComparatorCompare
( const Comparator *comparator, const void *str_1, const void *str_2 )
{
  return strcmp( str_1, str_2 );
}
