#ifndef __STUMPLESS_TEST_FUNCTION_FORMATTER_TEXT_H
#define __STUMPLESS_TEST_FUNCTION_FORMATTER_TEXT_H

/**
 * @file
 * Tests for the TextFormatter data structure.
 */

/**
 * Tests the EventToText function.
 *
 * @test A NULL Event must return a NULL Output. Each piece of the Event must
 * be present in the resulting Output string. Events missing various elements
 * must still be formatted.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEvent
( void );

/**
 * Tests the EventAttributeToText function.
 *
 * @test A NULL EventAttribute must return a NULL Output.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEventAttribute
( void );

/**
 * Tests the EventAttributesToText function.
 *
 * @test A NULL Dictionary must return a NULL Output.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEventAttributes
( void );

/**
 * Tests the initializer for the Text formatter.
 *
 * @test The function must return a non-NULL value when given the argument
 * "text". The provided Formatter must have a name equal to "text" and have a
 * format function of RecordToText.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestInitializer
( void );

/**
 * Tests the LevelToText function.
 *
 * @test A NULL Level must return a NULL Output.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestLevel
( void );

/**
 * Tests the RecordToText function.
 *
 * @test A NULL Record must return a NULL Output. Records with various parts
 * must include the present pieces and be in the correct format. Records missing
 * certain pieces must still be formatted.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecord
( void );

/**
 * Test the RecordAttributeToText function.
 *
 * @test A NULL RecordAttribute must return a NULL Output.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordAttribute
( void );

/**
 * Tests the RecordAttributesToText function.
 *
 * @test A NULL Dictionary must return a NULL Output.
 *
 * @todo implement
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordAttributes
( void );

#endif
