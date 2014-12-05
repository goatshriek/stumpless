#ifndef __STUMPLESS_TEST_FUNCTION_BOOLEAN_H
#define __STUMPLESS_TEST_FUNCTION_BOOLEAN_H

/**
 * @file
 * Functions for testing Boolean and related functions.
 */

/**
 * Test the BooleanToString function.
 *
 * @test A NULL argument must return NULL. A valid Boolean must return a
 * non-NULL string.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestToString
( void );

#endif
