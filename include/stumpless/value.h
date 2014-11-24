#ifndef __STUMPLESS_VALUE_H
#define __STUMPLESS_VALUE_H

/**
 * @file
 * Functions for dealing with Values.
 */

#include <stumpless/type.h>

ValueList *
BooleanArrayValueToValueList
( const Value * );

Status *
BooleanValueIntoString
( char *, const Value * );

char *
BooleanValueToString
( const Value * );

ValueList *
CharArrayValueToValueList
( const Value * );

Status *
CharValueIntoString
( char *, const Value * );

char *
CharValueToString
( const Value * );

Value *
CopyValue
( const Value * );

void
DestroyValue
( Value * );

ValueList *
DoubleArrayValueToValueList
( const Value * );

Status *
DoubleValueIntoString
( char *, const Value * );

char *
DoubleValueToString
( const Value * );

ValueList *
FloatArrayValueToValueList
( const Value * );

Status *
FloatValueIntoString
( char *, const Value * );

char *
FloatValueToString
( const Value * );

ValueList *
IntArrayValueToValueList
( const Value * );

Status *
IntValueIntoString
( char *, const Value * );

char *
IntValueToString
( const Value * );

ValueList *
LongArrayValueToValueList
( const Value * );

Status *
LongValueIntoString
( char *, const Value * );

char *
LongValueToString
( const Value * );

ValueList *
LongDoubleArrayValueToValueList
( const Value * );

Status *
LongDoubleValueIntoString
( char *, const Value * );

char *
LongDoubleValueToString
( const Value * );

ValueList *
LongLongArrayValueToValueList
( const Value * );

Status *
LongLongValueIntoString
( char *, const Value * );

char *
LongLongValueToString
( const Value * );

ValueList *
ShortArrayValueToValueList
( const Value * );

Status *
ShortValueIntoString
( char *, const Value * );

char *
ShortValueToString
( const Value * );

ValueList *
SignedCharArrayValueToValueList
( const Value * );

Status *
SignedCharValueIntoString
( char *, const Value * );

char *
SignedCharValueToString
( const Value * );

ValueList *
StringArrayValueToValueList
( const Value * );

Status *
StringValueIntoString
( char *, const Value * );

char *
StringValueToString
( const Value * );

ValueList *
UnsignedCharArrayValueToValueList
( const Value * );

Status *
UnsignedCharValueIntoString
( char *, const Value * );

char *
UnsignedCharValueToString
( const Value * );

ValueList *
UnsignedIntArrayValueToValueList
( const Value * );

Status *
UnsignedIntValueIntoString
( char *, const Value * );

char *
UnsignedIntValueToString
( const Value * );

ValueList *
UnsignedLongArrayValueToValueList
( const Value * );

Status *
UnsignedLongValueIntoString
( char *, const Value * );

char *
UnsignedLongValueToString
( const Value * );

ValueList *
UnsignedLongLongArrayValueToValueList
( const Value * );

Status *
UnsignedLongLongValueIntoString
( char *, const Value * );

char *
UnsignedLongLongValueToString
( const Value * );

ValueList *
UnsignedShortArrayValueToValueList
( const Value * );

Status *
UnsignedShortValueIntoString
( char *, const Value * );

char *
UnsignedShortValueToString
( const Value * );

Status *
ValueIntoString
( char *, const Value * );

Status *
ValueIntoString
( char *, const Value * );

char *
ValueToString
( const Value * );

ValueList *
ValueToValueList
( const Value * );

/**
 * Breaks a single Value representing an array of void pointers into a ValueList
 * of Values representing single void pointers.
 * @todo implement
 *
 * @param value the Value to break into a ValueList
 *
 * @return a new ValueList holding each void pointer
 */
ValueList *
VoidArrayValueToValueList
( const Value *value );

/**
 * Puts a string representation of a Value representing a void pointer into a
 * provided string.
 * @todo implement
 *
 * @param str a char buffer to put the string into
 * @param value the Value to get a string representation of
 *
 * @return a Status for the operation
 */
Status *
VoidValueIntoString
( char *str, const Value *value );

/**
 * Creates a string representation of a Value representing a void pointer.
 * @todo implement
 *
 * @param value the Value to get a string representation of
 *
 * @return a new string representing the Value
 */
char *
VoidValueToString
( const Value *value );

#endif
