#include "stumpless/comparator_list.h"

#include "private/comparator_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list, __STUMPLESS_NAME( Comparator ) * comparator )
{
  return AppendToComparatorList( list, comparator );
}

__STUMPLESS_NAME( Comparator ) *
__STUMPLESS_NAME( BeginComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return BeginComparatorList( list );
}

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( CopyComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return CopyComparatorList( list );
}

void
__STUMPLESS_NAME( DestroyComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  DestroyComparatorList( list );
}

unsigned short
__STUMPLESS_NAME( ComparatorListIsEmpty )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return ComparatorListIsEmpty( list );
}

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( NewComparatorList )
( void )
{
  return NewComparatorList();
}

__STUMPLESS_NAME( Comparator ) *
__STUMPLESS_NAME( NextInComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return NextInComparatorList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list, __STUMPLESS_NAME( Comparator ) * comparator )
{
  return PrependToComparatorList( list, comparator );
}

short
__STUMPLESS_NAME( RunComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list, const void * value_1, const void * value_2 )
{
  return RunComparatorList( list, value_1, value_2 );
}
