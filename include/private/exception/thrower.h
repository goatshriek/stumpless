#ifndef __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H
#define __STUMPLESS_PRIVATE_EXCEPTION_THROWER_H

#include <stumpless/type.h>

/**
 * Creates and throws a MemoryAllocationException.
 *
 * @return the new MemoryAllocationException
 */
Exception *
ThrowMemoryAllocationException
( void );

#endif
