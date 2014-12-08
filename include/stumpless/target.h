#ifndef __STUMPLESS_TARGET_H
#define __STUMPLESS_TARGET_H

/**
 * @file
 * Functions supporting the Target structure.
 */

#include <stumpless/type.h>

/**
 * Creates a copy of a provided Target.
 *
 * @param target the Target to create a copy of
 *
 * @return a copy of the original Target
 */
Target *
CopyTarget
( const Target *target );

/**
 * Destroys a provided Target.
 *
 * @param target the Target to destroy
 */
void
DestroyTarget
( Target *target );

/**
 * Logs a Record to a specified Target.
 *
 * @param target the Target to log the Record to
 * @param record the Record to log
 *
 * @return a Status for the result of operation
 */
Status *
LogToTarget
( Target *target, const Record *record );

#endif
