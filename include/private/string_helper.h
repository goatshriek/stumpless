#ifndef __STUMPLESS_PRIVATE_STRING_HELPER_H
#define __STUMPLESS_PRIVATE_STRING_HELPER_H

/**
 * @file
 * Helper functions for working with strings.
 */

#include <stumpless/config/check.h>

#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
# define SAFE_SPRINTF( str, length, format, ... ) sprintf_s( str, length, format, __VA_ARGS__ )
#else
# define SAFE_SPRINTF( str, length, format, ... ) snprintf( str, length, format, __VA_ARGS__ )
#endif

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

#endif
