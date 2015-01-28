#ifndef __STUMPLESS_VALUE_H
#define __STUMPLESS_VALUE_H

/**
 * @file
 * Functions for dealing with Values.
 */

#include <stumpless/type.h>

/**
 * Writes the provided value containing an array of Boolean structures into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
BooleanArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
BooleanArrayValueToValueList
( const Value * );

char *
BooleanValueIntoString
( char *, const Value *, size_t );

char *
BooleanValueToString
( const Value * );

/**
 * Writes the provided value containing an array of chars into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
CharArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
CharArrayValueToValueList
( const Value * );

char *
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

/**
 * Writes the provided value containing an array of doubles into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
DoubleArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
DoubleArrayValueToValueList
( const Value * );

char *
DoubleValueIntoString
( char *, const Value *, size_t );

char *
DoubleValueToString
( const Value * );

/**
 * Writes the provided value containing an array of floats into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
FloatArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
FloatArrayValueToValueList
( const Value * );

char *
FloatValueIntoString
( char *, const Value *, size_t );

char *
FloatValueToString
( const Value * );

/**
 * Writes the provided value containing an array of ints into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
IntArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
IntArrayValueToValueList
( const Value * );

char *
IntValueIntoString
( char *, const Value *, size_t );

char *
IntValueToString
( const Value * );

/**
 * Writes the provided value containing an array of longs into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
LongArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
LongArrayValueToValueList
( const Value * );

char *
LongValueIntoString
( char *, const Value *, size_t );

char *
LongValueToString
( const Value * );

/**
 * Writes the provided value containing an array of long doubles into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
LongDoubleArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
LongDoubleArrayValueToValueList
( const Value * );

char *
LongDoubleValueIntoString
( char *, const Value *, size_t );

char *
LongDoubleValueToString
( const Value * );

/**
 * Writes the provided value containing an array of long longs into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
LongLongArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
LongLongArrayValueToValueList
( const Value * );

char *
LongLongValueIntoString
( char *, const Value *, size_t );

char *
LongLongValueToString
( const Value * );

/**
 * Writes the provided value containing an array of shorts into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
ShortArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
ShortArrayValueToValueList
( const Value * );

char *
ShortValueIntoString
( char *, const Value *, size_t );

char *
ShortValueToString
( const Value * );

/**
 * Writes the provided value containing an array of signed chars into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
SignedCharArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
SignedCharArrayValueToValueList
( const Value * );

char *
SignedCharValueIntoString
( char *, const Value *, size_t );

char *
SignedCharValueToString
( const Value * );

/**
 * Writes the provided value containing an array of strings into the provided
 * string. No more than length characters are written. The string will be NULL
 * terminated unless the length parameter is not large enough to hold the entire
 * string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
StringArrayValueIntoString
( char *str, const Value *value, size_t length );

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
 * @return str
 */
char *
StringValueIntoString
( char *str, const Value *value, size_t length );

char *
StringValueToString
( const Value * );

/**
 * Writes the provided value containing an array of unsigned chars into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
UnsignedCharArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
UnsignedCharArrayValueToValueList
( const Value * );

char *
UnsignedCharValueIntoString
( char *, const Value *, size_t );

char *
UnsignedCharValueToString
( const Value * );

/**
 * Writes the provided value containing an array of unsigned ints into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
UnsignedIntArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
UnsignedIntArrayValueToValueList
( const Value * );

char *
UnsignedIntValueIntoString
( char *, const Value *, size_t );

char *
UnsignedIntValueToString
( const Value * );

/**
 * Writes the provided value containing an array of unsigned longs into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
UnsignedLongArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
UnsignedLongArrayValueToValueList
( const Value * );

char *
UnsignedLongValueIntoString
( char *, const Value *, size_t );

char *
UnsignedLongValueToString
( const Value * );

/**
 * Writes the provided value containing an array of unsigned long longs into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
UnsignedLongLongArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
UnsignedLongLongArrayValueToValueList
( const Value * );

char *
UnsignedLongLongValueIntoString
( char *, const Value *, size_t );

char *
UnsignedLongLongValueToString
( const Value * );

/**
 * Writes the provided value containing an array of unsigned shorts into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough to hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
UnsignedShortArrayValueIntoString
( char *str, const Value *value, size_t length );

ValueList *
UnsignedShortArrayValueToValueList
( const Value * );

char *
UnsignedShortValueIntoString
( char *, const Value *, size_t );

char *
UnsignedShortValueToString
( const Value * );

char *
ValueIntoString
( char *, const Value *, size_t );

char *
ValueToString
( const Value * );

ValueList *
ValueToValueList
( const Value * );

/**
 * Writes the provided value containing an array of void pointers into the
 * provided string. No more than length characters are written. The string will
 * be NULL terminated unless the length parameter is not large enough tod hold
 * the entire string, in which case the string may not be NULL terminated.
 *
 * @param str the char buffer to be written into
 * @param value the Value to be written to the string
 * @param length the maximum number of characters to write into the buffer
 *
 * @return str
 */
char *
VoidArrayValueIntoString
( char *str, const Value *value, size_t length );

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
 * @return str
 */
char *
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
