#ifndef __STUMPLESS_PRIVATE_CONTAINER_LIST_VALUE_H
#define __STUMPLESS_PRIVATE_CONTAINER_LIST_VALUE_H

#include <stdio.h>

#include "private/type.h"

ValueList *
AddSeparatorToValueList
( ValueList *, Value * );

/**
 * Creates a new Value for the character and adds it to the end
 * of the ValueList.
 *
 * @param list the ValueList to add the new Value to
 * @param character the char to create the Value from
 *
 * @return the ValueList appended to, or NULL on failure
 */
ValueList *
AppendCharToValueList
( ValueList *list, char character );

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

ValueListIterator *
BeginValueList
( ValueList * );

ValueListConstIterator *
CBeginValueList
( const ValueList * );

ValueListConstIterator *
CEndValueList
( const ValueList * );

ValueList *
CopyValueList
( const ValueList * );

ValueListConstReverseIterator *
CRBeginValueList
( const ValueList * );

ValueListConstReverseIterator *
CREndValueList
( const ValueList * );

void
DestroyValueList
( ValueList * );

ValueListIterator *
EndValueList
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

ValueListReverseIterator *
RBeginValueList
( ValueList * );

ValueListReverseIterator *
REndValueList
( ValueList * );

Value *
ValueListBack
( const ValueList * );

unsigned short
ValueListContains
( const ValueList *, const Value * );

Value *
ValueListFront
( const ValueList * );

/**
 * Puts the given ValueList into the string provided. Will write a maximum of
 * characters provided by length and stop, which may result in a string that is
 * not NULL terminated.
 *
 * @param str the char buffer to write the string to
 * @param list the ValueList to write into the string
 * @param length the maximum number of characters to write
 *
 * @return str
 */
char *
ValueListIntoString
( char *str, const ValueList *list, size_t length );

unsigned short
ValueListIsEmpty
( const ValueList * );

unsigned
ValueListSize
( const ValueList * );

char *
ValueListToString
( const ValueList * );

ValueList *
ValueListToStrings
( const ValueList * );

#endif
