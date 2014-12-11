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
( char *, const Value *, size_t );

char *
BooleanValueToString
( const Value * );

ValueList *
CharArrayValueToValueList
( const Value * );

Status *
CharValueIntoString
( char *, const Value *, size_t );

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
( char *, const Value *, size_t );

char *
DoubleValueToString
( const Value * );

ValueList *
FloatArrayValueToValueList
( const Value * );

Status *
FloatValueIntoString
( char *, const Value *, size_t );

char *
FloatValueToString
( const Value * );

ValueList *
IntArrayValueToValueList
( const Value * );

Status *
IntValueIntoString
( char *, const Value *, size_t );

char *
IntValueToString
( const Value * );

ValueList *
LongArrayValueToValueList
( const Value * );

Status *
LongValueIntoString
( char *, const Value *, size_t );

char *
LongValueToString
( const Value * );

ValueList *
LongDoubleArrayValueToValueList
( const Value * );

Status *
LongDoubleValueIntoString
( char *, const Value *, size_t );

char *
LongDoubleValueToString
( const Value * );

ValueList *
LongLongArrayValueToValueList
( const Value * );

Status *
LongLongValueIntoString
( char *, const Value *, size_t );

char *
LongLongValueToString
( const Value * );

ValueList *
ShortArrayValueToValueList
( const Value * );

Status *
ShortValueIntoString
( char *, const Value *, size_t );

char *
ShortValueToString
( const Value * );

ValueList *
SignedCharArrayValueToValueList
( const Value * );

Status *
SignedCharValueIntoString
( char *, const Value *, size_t );

char *
SignedCharValueToString
( const Value * );

ValueList *
StringArrayValueToValueList
( const Value * );

/**
 * Writes a string representing the provided value into the character buffer
 * provided. Only writes up to length characters and stops. This means that the
 * resulting string may  not be NULL-terminated.
 *
 * @param str the character buffer to write the string into
 * @param value the value to get a string for
 * @param length the maximum number of character to write to the buffer
 *
 * @return a Status describing the operation
 */
Status *
StringValueIntoString
( char *str, const Value *value, size_t length );

char *
StringValueToString
( const Value * );

ValueList *
UnsignedCharArrayValueToValueList
( const Value * );

Status *
UnsignedCharValueIntoString
( char *, const Value *, size_t );

char *
UnsignedCharValueToString
( const Value * );

ValueList *
UnsignedIntArrayValueToValueList
( const Value * );

Status *
UnsignedIntValueIntoString
( char *, const Value *, size_t );

char *
UnsignedIntValueToString
( const Value * );

ValueList *
UnsignedLongArrayValueToValueList
( const Value * );

Status *
UnsignedLongValueIntoString
( char *, const Value *, size_t );

char *
UnsignedLongValueToString
( const Value * );

ValueList *
UnsignedLongLongArrayValueToValueList
( const Value * );

Status *
UnsignedLongLongValueIntoString
( char *, const Value *, size_t );

char *
UnsignedLongLongValueToString
( const Value * );

ValueList *
UnsignedShortArrayValueToValueList
( const Value * );

Status *
UnsignedShortValueIntoString
( char *, const Value *, size_t );

char *
UnsignedShortValueToString
( const Value * );

Status *
ValueIntoString
( char *, const Value *, size_t );

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
 * @param length the maximum number of characters to write
 *
 * @return a Status for the operation
 */
Status *
VoidValueIntoString
( char *str, const Value *value, size_t length );

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
