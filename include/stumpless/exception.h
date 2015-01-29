#ifndef __STUMPLESS_EXCEPTION_H
#define __STUMPLESS_EXCEPTION_H

#include <stumpless/type.h>

/**
 * Adds an Exception to the list of registered Exceptions.
 *
 * @param e the Exception to add
 *
 * @return the Exception that was added, or NULL on failure
 */
Exception *
AddException
( Exception *e );

/**
 * Destroys the provided Exception. If the exception exists in the list of
 * registered Exceptions, it is removed.
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

/**
 * Finds an Exception with the provided name in the list of registered
 * Exceptions.
 *
 * @param name the name to search for
 *
 * @return the Exception with the provided name, or NULL if one cannot be found
 */
Exception *
FindExceptionByName
( const char *name );

#endif
