#ifndef __STUMPLESS_EXCEPTION_HANDLER_H
#define __STUMPLESS_EXCEPTION_HANDLER_H

/**
 * @file
 * Functions for setting and getting custom Exception handlers.
 */

#include <stumpless/type.h>

/**
 * Returns the function called whenever a MemoryAllocationException is thrown.
 * A NULL is returned if no function is set to be called.
 *
 * @return the current handler set
 */
exception_handler_function_t
GetMemoryAllocationExceptionHandler
( void );

/**
 * Sets a function to be called any time a MemoryAllocationException is thrown.
 * The function will be passed the thrown Exception, or a NULL if the Exception
 * could not be created (for example a failed malloc call).
 *
 * @param handler the function to call when the Exception is raised
 */
void
SetMemoryAllocationExceptionHandler
( void (*handler)( const Exception * ) );

#endif
