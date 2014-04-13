#include <string.h>

#include "private/list.h"
#include "private/type.h"

#include "private/list/comparator.h"
#include "private/list/inheritance.h"
#include "private/list/iterator.h"

#include "private/list/const_iterator/comparator.h"

#include "private/list/const_reverse_iterator/comparator.h"

#include "private/list/iterator/comparator.h"

#include "private/list/reverse_iterator/comparator.h"

#include "static/list/comparator.h"

ADD_SEPARATOR_TO_LIST( Comparator )

APPEND_LISTS( Comparator )

APPEND_TO_LIST( Comparator )

BEGIN_LIST( Comparator )

CBEGIN_LIST( Comparator )

CEND_LIST( Comparator )

LIST_CONTAINS( Comparator )

LIST_IS_EMPTY( Comparator )

LIST_SIZE( Comparator )

COPY_LIST( Comparator )

CRBEGIN_LIST( Comparator )

CREND_LIST( Comparator )

DESTROY_LIST( Comparator )

END_LIST( Comparator )

NEW_LIST( Comparator )

PREPEND_TO_LIST( Comparator )

RBEGIN_LIST( Comparator )

REND_LIST( Comparator )

short
RunComparatorList
( ComparatorList * list, const void * value_1, const void * value_2 )
{
  if( ComparatorListIsEmpty( list ) )
    return 0;
  
  short result;
  Comparator * comparator;
  ListIterator * iterator = BeginList( list->list );
  while( comparator = NextInListIterator( iterator ) ){
    result = comparator->compare( value_1, value_2, comparator->options );
    
    if( result != 0 ){
      DestroyListIterator( iterator );
      return result;
    }
  }
  
  DestroyListIterator( iterator );
  return 0;
}
