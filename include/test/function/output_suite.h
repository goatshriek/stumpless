#ifndef __STUMPLESS_TEST_FUNCTION_OUTPUT_H
#define __STUMPLESS_TEST_FUNCTION_OUTPUT_H

/**
 * @file
 * Tests for the Output data structure.
 */

/**
 * Tests the DestroyOutput function.
 *
 * @test A NULL Output must not cause an error. A populated Output must not
 * cause an error.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
( void );

#endif
