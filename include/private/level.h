#ifndef __STUMPLESS_PRIVATE_LEVEL_H
#define __STUMPLESS_PRIVATE_LEVEL_H

/**
 * @file
 * All functions for finding and working with Levels.
 */

#include "private/type.h"

/**
 * Adds a Level to the overall list. This allows it to be returned by the
 * FindLevelByName function. Levels added here must have a unique name or they
 * will not be accepted.
 *
 * @param level the Level to add to the list of Levels
 * @return a Exception for the addition operation
 */
Exception *
AddLevel
( Level *level );

/**
 * Finds a Level with the name specified. If the Level exists and has not been
 * initialized, it is initialized and then returned.
 *
 * @param name the name of the Level to return
 * @return the Level requested, or NULL if it cannot be found or initialized
 */
Level *
FindLevelByName
( const char *name );

/**
 * Creates a string that represents the specified Level. The format of the
 * string is identical to that of the TextFormatter format for a Level.
 *
 * @param level the level to get a string represtnation of
 * @return a pointer to a NULL-terminated string containing the representation
 */
char *
LevelToString
( const Level *level );

#endif
