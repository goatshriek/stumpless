#ifndef __STUMPLESS_TEST_FUNCTION_ADAPTER_H
#define __STUMPLESS_TEST_FUNCTION_ADAPTER_H

/**
 * @file
 * Functions for testing Adapters and related functions.
 */

/**
 * Test the AdaptRecord function.
 *
 * @test The last Adapter run and the last adapted Record must be set to the
 * appropriate values after running the function. The Record must have the
 * attribute added by the Adapter after the function. A NULL Record will return
 * a NULL, while a NULL Adapter returns the Record unchanged.
 *
 * @todo make sure that the Record has the new attribute
 * @todo make sure that the Record is unchanged if the Adapter is NULL
 * @todo test handling of malformed Adapters
 * 
 * @return NULL on completion, or a string describing the failure 
 */
const char *
TestAdapt
( void );

/**
 * Test the AddAdapter function.
 *
 * @test Once an Adapter is added, calling FindAdapterByName must return the
 * Adapter that was added.
 *
 * @todo add test for NULL argument
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAddAdapter
( void );

/**
 * Test the FindAdapterByName function.
 *
 * @test A predefined Adapter should be returned by a call to the function. The
 * correct Adapter (with the given name) must be returned.
 *
 * @todo add test for NULL argument
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestFindAdapterByName
( void );

/**
 * Test the GetAdapterOption function.
 *
 * @test Calling the function with a NULL adapter or a NULL or non-existent
 * option name returns NULL. The returned string must equal to the value the
 * option was set to.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetOption
( void );

/**
 * Test the SetAdapterOption function.
 *
 * @test Calling the function with a NULL Adapter, option name, or option value
 * must return an empty argument Status. Valid arguments for thee parameters
 * must return NULL.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestSetOption
( void );

#endif
