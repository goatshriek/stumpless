#ifndef __STUMPLESS_RECORD_ATTRIBUTE_H
#define __STUMPLESS_RECORD_ATTRIBUTE_H

#include <stumpless/type.h>

/**
 * Destroys the given RecordAttribute.
 *
 * @param attribute the RecordAttribute to destroy
 */
void
DestroyRecordAttribute
( RecordAttribute *attribute );

/**
 * Creates a new RecordAttribute with the supplied name. If a RecordAttribute
 * of the given name already exists, it is returned without creating a new
 * RecordAttribute.
 * 
 * @param name the name to give the new RecordAttribute
 *
 * @return the RecordAttribute with the given name or NULL on failure
 */
RecordAttribute *
NewRecordAttribute
( const char *name );

/**
 * Creates a Dictionary of RecordAttributes build from the supplied Dictionary
 * of EventAttributes.
 *
 * @param event_attributes a Dictionary of EventAttributes
 *
 * @return a Dictionary populated with new RecordAttributes
 */
Dictionary *
NewRecordAttributeDictionaryForEventAttributeDictionary
( const Dictionary *event_attributes );

/**
 * Creates a new RecordAttribute for the supplied EventAttribute. The
 * RecordAttribute is given the same name as the supplied EventAttribute, and if
 * this RecordAttribute already exists then it is simply returned.
 *
 * @param event_attribute the EventAttribute to create the RecordAttribute to
 *
 * @return the RecordAttribute for the provided EventAttribute or NULL on
 * failure
 */
RecordAttribute *
NewRecordAttributeForEventAttribute
( const EventAttribute *event_attribute );

#endif
