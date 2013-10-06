#ifndef STUMPLESS_PRIVATE_VALUE_LIST_H
#define STUMPLESS_PRIVATE_VALUE_LIST_H

#include <stdio.h>

#include "private/type.h"

Status *
AddSeparatorToValueList
( ValueList *, Value * );

Status *
AppendStringToValueList
( ValueList *, const char * );

Status *
AppendUnsignedIntToValueList
( ValueList *, unsigned );

Status *
AppendValueLists
( ValueList *, ValueList * );

Status *
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

Status *
PrependStringToValueList
( ValueList *, const char * );

Status *
PrependValueToValueList
( ValueList *, Value * );

Status *
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
