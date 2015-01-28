#ifndef __STUMPLESS_EVENT_H
#define __STUMPLESS_EVENT_H

/**
 * @file
 * All functions for finding and working with Events.
 */

#include <stumpless/type.h>

/**
 * Adds an Event to the overall list. This allows it to be returned by the
 * FindEventByName function. Events added here must have a unique name or they
 * will not be accepted.
 *
 * @param event the Event to add to the list of Events
 *
 * @return event
 */
Event *
AddEvent
( Event *event );

/**
 * Creates a string that represents the specified Event. The format of the
 * string is identical to that of the TextFormatter format for an Event.
 *
 * @param event the event to get a string representation of
 *
 * @return a pointer to a NULL-terminated string containing the representation
 */
char *
EventToString
( Event *event );

/**
 * Finds an Event with the name specified. If the Event exists and has not been
 * initialized, it is initialized and then returned.
 *
 * @param name the name of the Event to return
 * @return the Event requested, or NULL if it cannot be found or initialized
 */
Event *
FindEventByName
( const char *name );

#endif
