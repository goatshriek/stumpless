#include "private/list/comparator.h"

#include "stumpless/list/comparator.h"

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AddSeparatorToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list, __STUMPLESS_NAME( Comparator ) * separator )
{
  return AddSeparatorToComparatorList( list, separator );
}

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AppendComparatorLists )
( __STUMPLESS_NAME( ComparatorList ) * first, __STUMPLESS_NAME( ComparatorList ) * second )
{
  return AppendComparatorLists( first, second );
}

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( AppendToComparatorList )
( __STUMPLESS_NAME( ComparatorList ) * list, __STUMPLESS_NAME( Comparator ) * comparator )
{
  return AppendToComparatorList( list, comparator );
}

unsigned short
__STUMPLESS_NAME( ComparatorListContains )
( __STUMPLESS_NAME( ComparatorList ) * list, __STUMPLESS_NAME( Comparator ) * comparator )
{
  return ComparatorListContains( list, comparator );
}

unsigned short
__STUMPLESS_NAME( ComparatorListIsEmpty )
( __STUMPLESS_NAME( ComparatorList ) * list )
{
  return ComparatorListIsEmpty( list );
}

unsigned
__STUMPLESS_NAME( ComparatorListSize )
( const __STUMPLESS_NAME( ComparatorList ) * list )
{
  return ComparatorListSize( list );
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

__STUMPLESS_NAME( ComparatorList ) *
__STUMPLESS_NAME( NewComparatorList )
( void )
{
  return NewComparatorList();
}

__STUMPLESS_NAME( ComparatorList ) *
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
