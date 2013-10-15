#ifndef __STUMPLESS_VALUE_LIST_H
#define __STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddSeparatorToValueList )
( __STUMPLESS_NAME( ValueList ) *, __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendStringToValueList )
( __STUMPLESS_NAME( ValueList ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendUnsignedIntToValueList )
( __STUMPLESS_NAME( ValueList ) *, unsigned );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendValueLists )
( __STUMPLESS_NAME( ValueList ) *, __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendValueToValueList )
( __STUMPLESS_NAME( ValueList ) *, __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( CopyValueList )
( __STUMPLESS_NAME( ValueList ) * );

void
__STUMPLESS_NAME( DestroyValueList )
( __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( NewValueList )( void );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( NextInValueList )
( __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependStringToValueList )
( __STUMPLESS_NAME( ValueList ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependValueToValueList )
( __STUMPLESS_NAME( ValueList ) *, __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( StartValueList )
( __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ValueListIntoString )
( char *, __STUMPLESS_NAME( ValueList ) * );

unsigned short
__STUMPLESS_NAME( ValueListIsEmpty )( __STUMPLESS_NAME( ValueList ) * );

char *
__STUMPLESS_NAME( ValueListToString )( __STUMPLESS_NAME( ValueList ) * );

__STUMPLESS_NAME( ValueList ) *
__STUMPLESS_NAME( ValueListToStrings )( __STUMPLESS_NAME( ValueList ) * );

#endif
