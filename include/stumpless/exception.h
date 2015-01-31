#ifndef __STUMPLESS_EXCEPTION_H
#define __STUMPLESS_EXCEPTION_H

#include <stumpless/type.h>

/**
 * Marks the Exception provided as dealt with. The Exception will be destroyed
 * after this call.
 *
 * @param e the Exception to catch.
 */
void
CatchException
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
 * Gives the next uncaught Exception. Exceptions are returned in the order
 * thrown.
 *
 * @return the last Exception thrown, or NULL if one has not been thrown
 */
Exception *
GetNextException
( void );

#endif
