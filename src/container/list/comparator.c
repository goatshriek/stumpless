#include <string.h>

#include "private/container/list.h"
#include "private/type.h"

#include "private/container/list/comparator.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"

#include "private/container/list/const_iterator/comparator.h"

#include "private/container/list/const_reverse_iterator/comparator.h"

#include "private/container/list/iterator/comparator.h"

#include "private/container/list/reverse_iterator/comparator.h"

#include "static/container/list/comparator.h"

ADD_SEPARATOR_TO_LIST( Comparator )

APPEND_LISTS( Comparator )

APPEND_TO_LIST( Comparator )

BEGIN_LIST( Comparator )

CBEGIN_LIST( Comparator )

CEND_LIST( Comparator )

LIST_BACK( Comparator )

LIST_CONTAINS( Comparator )

LIST_FRONT( Comparator )

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
( ComparatorList *list, const void *value_1, const void *value_2 )
{
  Comparator *comparator;
  ListIterator *iterator;
  short result;

  if( ComparatorListIsEmpty( list ) )
    return 0;

  iterator = BeginList( list->list );
  while( comparator = NextInListIterator( iterator ) ){
    result = comparator->compare( comparator, value_1, value_2 );

    if( result != 0 ){
      DestroyListIterator( iterator );
      return result;
    }
  }

  DestroyListIterator( iterator );
  return 0;
}
