#ifndef __STUMPLESS_TEST_FUNCTION_VALUE_CONSTRUCTOR_H
#define __STUMPLESS_TEST_FUNCTION_VALUE_CONSTRUCTOR_H

/**
 * @file
 * Tests for the value constructor functions.
 */

/**
 * Tests the ValueForVoid function.
 *
 * @test A NULL void pointer returns a NULL Value. The created Value must have
 * the same pointer assigned to it.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestVoid
( void );

#endif
