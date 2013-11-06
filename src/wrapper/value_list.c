#include "stumpless/value_list.h"

#include "private/value_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddSeparatorToValueList )
( __STUMPLESS_NAME( ValueList ) * list, __STUMPLESS_NAME( Value ) * value )
{
  return AddSeparatorToValueList( list, value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendStringToValueList )
( __STUMPLESS_NAME( ValueList ) * list, const char * str )
{
  return AppendStringToValueList( list, str );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendUnsignedIntToValueList )
( __STUMPLESS_NAME( ValueList ) * list, unsigned num )
{
  return AppendUnsignedIntToValueList( list, num );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendValueLists )
( __STUMPLESS_NAME( ValueList ) * list, __STUMPLESS_NAME( ValueList ) * next )
{
  return AppendValueLists( list, next );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendValueToValueList )
( __STUMPLESS_NAME( ValueList ) * list, __STUMPLESS_NAME( Value ) * value )
{
  return AppendValueToValueList( list, value );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( BeginValueList )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return BeginValueList( list );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( CopyValueList )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return CopyValueList( list );
}

void
__STUMPLESS_NAME( DestroyValueList )
( __STUMPLESS_NAME( ValueList ) * list )
{
  DestroyValueList( list );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( NewValueList )
( void )
{
  return NewValueList();
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( NextInValueList )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return NextInValueList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependStringToValueList )
( __STUMPLESS_NAME( ValueList ) * list, const char * str )
{
  return PrependStringToValueList( list, str );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependValueToValueList )
( __STUMPLESS_NAME( ValueList ) * list, __STUMPLESS_NAME( Value ) * value )
{
  return PrependValueToValueList( list, value );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ValueListIntoString )
( char * str, __STUMPLESS_NAME( ValueList ) * list )
{
  return ValueListIntoString( str, list );
}

unsigned short
__STUMPLESS_NAME( ValueListIsEmpty )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return ValueListIsEmpty( list );
}

char *
__STUMPLESS_NAME( ValueListToString )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return ValueListToString( list );
}

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ValueListToStrings )
( __STUMPLESS_NAME( ValueList ) * list )
{
  return ValueListToStrings( list );
}
