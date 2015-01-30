#ifndef __STUMPLESS_EXCEPTION_H
#define __STUMPLESS_EXCEPTION_H

#include <stumpless/type.h>

/**
 * Destroys the provided Exception.
 *
 * @param e the Exception to destroy
 */
void
DestroyException
( Exception *e );

/**
 * Returns a new string representation of the provided Exception.
 *
 * @param e the Exception to get a string representation of
 *
 * @return a new string representing the Exception
 */
char *
ExceptionToString
( Exception *e );

#endif
