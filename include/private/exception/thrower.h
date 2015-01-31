#ifndef __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H
#define __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H

#include "private/type.h"

/**
 * Returns the current Queue of all uncaught Exceptions.
 *
 * @return a Queue of all current Exceptions
 */
Queue *
GetExceptionStack
( void );

/**
 * Creates and throws a MemoryAllocationException.
 *
 * @return the new MemoryAllocationException
 */
Exception *
ThrowMemoryAllocationException
( void );

#endif
