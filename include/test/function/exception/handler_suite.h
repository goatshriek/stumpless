#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_HANDLER_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_HANDLER_H

/**
 * @file
 * Tests for the Exception handler functionality.
 */

/**
 * Tests the GetMemoryAllocationExceptionHandler function.
 *
 * @test After a handler is set, it must be returned by the function. If the
 * handler is set to NULL, NULL must be returned by the function.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetMemoryAllocationExceptionHandler
( void );

/**
 * Tests the SetMemoryAllocationExceptionHandler function.
 *
 * @test After the handler is set to a function, when the Exception is thrown
 * the function must be called. If the handler is set to NULL, then the function
 * will no longer be called.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestSetMemoryAllocationExceptionHandler
( void );

#endif
