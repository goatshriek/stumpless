#ifndef __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H
#define __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H

#include "private/type.h"

/**
 * Destroys the provided Exception, and removes it from the list of active
 * (uncaught) Exceptions.
 *
 * @param e the Exception to destroy
 */
void
DestroyException
( Exception *e );

/**
 * Returns the first Exception thrown that has not yet been caught.
 *
 * @return the first uncaught Exception
 */
Exception *
GetNextException
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
