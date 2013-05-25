#ifndef STUMPLESS_STRING_HELPER_H
#define STUMPLESS_STRING_HELPER_H

char *
copy_string( const char * );

// returns 0 if the string contains anything other than whitespace
// otherwise returns a non-zero value (the length of the string, or
// 1 for a NULL pointer)
unsigned short
is_empty( const char * );

// replaces every target character in the given string with the replacement
// character (first char is target, second is replacement)
char *
replace_char( const char *, char, char );

// converts the first letter of a word to uppercase
// a word is defined as any series of characters starting with a letter which
// is preceded by whitespace
char *
title_case( const char * );

#endif
