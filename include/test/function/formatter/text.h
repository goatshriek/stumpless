#ifndef __STUMPLESS_TEST_FUNCTION_FORMATTER_TEXT_H
#define __STUMPLESS_TEST_FUNCTION_FORMATTER_TEXT_H

/**
 * @file
 * Tests for the TextFormatter data structure.
 *
 * @todo break NULL checks into separate test functions
 * @todo add ValuetoText function tests
 */

/**
 * Tests the EventToText function.
 *
 * @test A NULL Event or Formatter must return a NULL Output. An Event with a
 * name, level, and attributes must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEvent
( void );

/**
 * Tests the EventAttributeToText function.
 *
 * @test A NULL EventAttribute or Formatter must return a NULL Output. An
 * EventAttribute with a default value must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEventAttribute
( void );

/**
 * Tests the EventAttributesToText function.
 *
 * @test A NULL Dictionary or Formatter must return a NULL Output. A Dictionary
 * containing at least one EventAttribute without a default value and one with a
 * default value must be properly formatted.
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
 * @test A NULL Level or Formatter must return a NULL Output. A Level with three
 * levels and a name must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestLevel
( void );

/**
 * Tests the RecordToText function.
 *
 * @test A NULL Record or Formatter must return a NULL Output. A Record with at
 * least one RecordAttribute that has no EventAttribute, one using the default
 * Value, one using a custom Value, and an Event with at least one Attribute not
 * used in the Record must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecord
( void );

/**
 * Test the RecordAttributeToText function.
 *
 * @test A NULL RecordAttribute or Formatter must return a NULL Output. A
 * RecordAttribute with a value must be properly formatted. A RecordAttribute
 * using the default value must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordAttribute
( void );

/**
 * Tests the RecordAttributesToText function.
 *
 * @test A NULL Dictionary or Formatter must return a NULL Output. A Dictionary
 * containing at least one RecordAttribute with no EventAttribute, one without a
 * Value assigned, and one with a Value assigned must be properly formatted.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordAttributes
( void );

#endif
