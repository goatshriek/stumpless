#ifndef __STUMPLESS_LIST_VALUE_H
#define __STUMPLESS_LIST_VALUE_H

#include <stumpless/type.h>

ValueList *
AddSeparatorToValueList
( ValueList *, Value * );

ValueList *
AppendStringToValueList
( ValueList *, const char * );

ValueList *
AppendToValueList
( ValueList *, Value * );

ValueList *
AppendUnsignedIntToValueList
( ValueList *, unsigned );

ValueList *
AppendValueLists
( ValueList *, ValueList * );

ValueList *
CopyValueList
( ValueList * );

void
DestroyValueList
( ValueList * );

ValueList *
NewValueList
( void );

ValueList *
PrependStringToValueList
( ValueList *, const char * );

ValueList *
PrependToValueList
( ValueList *, Value * );

unsigned short
ValueListContains
( const ValueList *, const Value * );

Status *
ValueListIntoString
( char *, ValueList * );

unsigned short
ValueListIsEmpty
( ValueList * );

unsigned
ValueListSize
( const ValueList * );

char *
ValueListToString
( ValueList * );

ValueList *
ValueListToStrings
( ValueList * );

#endif
