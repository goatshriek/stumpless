#ifndef __STUMPLESS_PRIVATE_STRING_HELPER_H
#define __STUMPLESS_PRIVATE_STRING_HELPER_H

/**
 * @file
 * Helper functions for working with strings.
 */

#include <stdarg.h>

#include <stumpless/config/check.h>

char *
copy_string
( const char * );

// creates a new string with the first letter of each word to uppercase
// a word is defined as any series of characters starting with a letter which
// is preceded by whitespace
// returns a pointer to the new string
char *
get_title_case
( const char * );

// returns 0 if the string contains anything other than whitespace
// otherwise returns a non-zero value (the length of the string, or
// 1 for a NULL pointer)
unsigned short
is_empty
( const char * );

// replaces every target character in the given string with the replacement
// character (first char is target, second is replacement)
char *
replace_char
( const char *, const char, char );

// starting at the beginning of the string, replaces the first occurence
// of the second string within the first string with the third string
// assumes that the string has enough space to accomodate the replacement
// returns a pointer to the modified string
char *
replace_first_string
( char *, const char *, const char * );

// starting at the beginning of the string, replaces each occurence of the
// second string within the first string with the third string
// assumes that the string has enough space to accomodate replacements
// recursive replacements are not supported (if the target string does not
// exist in the original string, it is not replaced)
// returns a pointer to the modified string
char *
replace_string
( char *, const char *, const char * );

/**
 * Composes a string with the same text that would be printed if format was
 * used on printf, but instead of being printed, the content is stored as string
 * in the buffer pointed by str (taking length as the maximum buffer capacity to
 * fill).
 *
 * If the resulting string would be longer than length-1 characters, the
 * remaining characters are discarded and not stored, but counted for the value
 * returned by the function.
 *
 * A terminating null character is automatically appended after the content
 * written.
 *
 * After the format parameter, the function expects at least as many additional
 * arguments as needed for format.
 *
 * @param str the buffer to write into
 * @param length the size of the buffer to write to
 * @param format the format string to use for the printing
 *
 * @return the number of characters written to the buffer. If an error is
 * encountered a negative value is returned.
 */
int
safe_sprintf
( char *str, size_t length, const char *format, ... );

/**
 * Copies the first length-1 characters of source to destination. A null
 * character is always placed at the end of the string.
 *
 * destination and source shall not overlap.
 *
 * @param destination the location for the copy of the string
 * @param source the string to copy
 * @param length the length of the destination buffer
 *
 * @return destination
 */
char *
safe_strncpy
( char *destination, const char *source, size_t length );

/**
 * Composes a string with the same text that would be printed if format was
 * used on printf, but using the elements in the variable argument list
 * identified by args instead of additional function arguments and storing the
 * resulting content as a string in the buffer pointed by str (taking length as
 * the maximum buffer capacity to fill).
 *
 * If the resulting string would be longer than length-1 characters, the
 * remaining characters are discarded and not stored, but counted for the value
 * returned by the function.
 *
 * Internally, the function retrieves arguments from the list identified by args
 * as if va_arg was used on it, and thus the state of args is likely to be
 * altered by the call.
 *
 * In any case, arg should have been initialized by va_start at some point
 * before the call, and it is expected to be released by va_end at some point
 * after the call.
 *
 * @param str the buffer to write into
 * @param length the size of the buffer to write to
 * @param format the format string to use for the printing
 *
 * @return the number of characters written to the buffer. If an error is
 * encountered a negative value is returned.
 */
int
vsafe_sprintf
( char *str, size_t length, const char *format, va_list args );

#endif
