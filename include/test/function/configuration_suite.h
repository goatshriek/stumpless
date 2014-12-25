#ifndef __STUMPLESS_TEST_FUNCTION_CONFIGURATION_H
#define __STUMPLESS_TEST_FUNCTION_CONFIGURATION_H

/**
 * @file
 * Functions for testing Configurations and related functions.
 */

/**
 * Test the InitializeConfiguration function.
 *
 * @test After calling the function, the Configuration returned by
 * GetConfiguration must not have a NULL configuration or member.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestInitialize
( void );

#endif
