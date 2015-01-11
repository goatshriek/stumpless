#ifndef STUMPLESS_EXCEPTION_H
#define STUMPLESS_EXCEPTION_H

#include "private/type.h"

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
 * Returns a new string representation of the provided Exception.
 *
 * @param e the Exception to get a string representation of
 *
 * @return a new string representing the Exception
 */
const char *
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

/**
 * Gets the last failure Exception raised.
 *
 * @return the last Exception classified as a failure, or NULL if one has not
 * been raised
 */
Exception *
GetLastFailureException
( void );

/**
 * Gets the last informational Exception raised.
 *
 * @return the last Exception classified as informational, or NULL if one has
 * not been raised
 */
Exception *
GetLastInformationalException
( void );

/**
 * Gets the last warning Exception raised.
 *
 * @return the last Exception classified as a warning, or NULL if one has not
 * been raised
 */
Exception *
GetLastWarningException
( void );

/**
 * Raises an Exception by setting all of its variables and returning it.
 * Functions that use this function to raise an Exception should return the
 * result of this function.
 *
 * @param str the name of the Exception to raise
 *
 * @return the raised Exception
 */
Exception *
RaiseException
( const char *str );

#endif
