#ifndef STUMPLESS_PRIVATE_VALUE_LIST_H
#define STUMPLESS_PRIVATE_VALUE_LIST_H

#include <stdio.h>

#include "private/type.h"

StatusCode
AddSeparatorToValueList
( ValueList *, Value * );

StatusCode
AppendStringToValueList
( ValueList *, const char * );

StatusCode
AppendUnsignedIntToValueList
( ValueList *, unsigned );

StatusCode
AppendValueLists
( ValueList *, ValueList * );

StatusCode
AppendValueToValueList
( ValueList *, Value * );

ValueList *
CopyValueList
( ValueList * );

void
DestroyValueList
( ValueList * );

ValueList *
NewValueList
( void );

StatusCode
PrependStringToValueList
( ValueList *, const char * );

StatusCode
PrependValueToValueList
( ValueList *, Value * );

StatusCode
ValueListIntoString
( char *, ValueList * );

unsigned short
ValueListIsEmpty
( ValueList * );

char *
ValueListToString
( ValueList * );

ValueList *
ValueListToStrings
( ValueList * );

#endif
