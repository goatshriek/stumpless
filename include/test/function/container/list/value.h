#ifndef __STUMPLESS_TEST_FUNCTION_CONTAINER_LIST_VALUE_H
#define __STUMPLESS_TEST_FUNCTION_CONTAINER_LIST_VALUE_H

/**
 * @file
 * Functions for testing ValueLists and related functions.
 */

/**
 * Tests the AppendCharToValueList function.
 *
 * @test Providing a NULL list must return NULL. A valid char returns the list
 * provided, and the last Value in the list does not equal the Value that was
 * last before the function call. After the function call the last Value must be
 * a char Value holding data equal to the supplied char.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAppendChar
( void );

#endif
