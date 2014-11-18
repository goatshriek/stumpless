#ifndef __STUMPLESS_FORMATTER_TEXT_H
#define __STUMPLESS_FORMATTER_TEXT_H

/**
 * @file
 * Functions text Formatters.
 */

#include <stumpless/type.h>

/**
 * Creates a text Output based on an Event.
 *
 * @param formatter the Formatter generating the Output
 * @param event the Event to create an Output for
 *
 * @return a text Output for the Event, or NULL on failure
 */
Output *
EventToText
( const Formatter *formatter, const Event *event );

/**
 * Creates a text Output based on an EventAttribute.
 *
 * @param formatter the Formatter generating the Output
 * @param attribute the EventAttribute to create an Output for
 *
 * @return a text Output for the attribute, or NULL on failure
 */
Output *
EventAttributeToText
( const Formatter *formatter, const EventAttribute *attribute );

/**
 * Creates a text Output based on a Dictionary of EventAttributes.
 *
 * @param formatter the Formatter generating the Output
 * @param attributes the Dictionary of EventAttributes to create an Output for
 *
 * @return a text Output for the attributes, or NULL on failure
 */
Output *
EventAttributesToText
( const Formatter *formatter, const Dictionary *attributes );

/**
 * Creates a text Output based on a Level.
 *
 * @param formatter the Formatter generating the Output
 * @param level the Level to create an Output for
 *
 * @return a text Output for the Level
 */
Output *
LevelToText
( const Formatter *formatter, const Level *level );

/**
 * Creates a text Output based on a Record.
 *
 * @param formatter the Formatter generating the Output
 * @param record the Record to create an Output for
 *
 * @return a text Output for the Record
 */
Output *
RecordToText
( const Formatter *formatter, const Record *record );

/**
 * Creates a text Output based on a RecordAttribute.
 *
 * @param formatter the Formatter generating the Output
 * @param attribute the RecordAttribute to create an Output for
 *
 * @return a text Output for the RecordAttribute
 */
Output *
RecordAttributeToText
( const Formatter *formatter, const RecordAttribute *attribute );

/**
 * Creates a text Output based on a Dictionary of RecordAttributes.
 *
 * @param formatter the Formatter generating the Output
 * @param attributes the Dictionary of RecordAttributes to create an Output for
 *
 * @return a text Output for the RecordAttributes
 */
Output *
RecordAttributesToText
( const Formatter *formatter, const Dictionary *attributes );

/**
 * Creates a text Output based on a Value.
 *
 * @param formatter the Formatter generating the Output
 * @param value the Value to create an Output for
 *
 * @return a text Output for the Value
 */
Output *
ValueToText
( const Formatter *formatter, const Value *value );

#endif
