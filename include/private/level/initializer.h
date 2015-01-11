#ifndef __STUMPLESS_PRIVATE_LEVEL_INITIALIZER_H
#define __STUMPLESS_PRIVATE_LEVEL_INITIALIZER_H

/** @file
 *  Functions to initialize default Levels.
 */

#include "private/level/initializer.h"
#include "private/type.h"

/**
 * @private
 * Initializes the Level of the given name. Initialization consists of the
 * creation of the Level struct and its addition to the list of Levels. Only
 * Levels provided by the library can be initialized this way; custom Levels
 * need to be manualy created and added to the list of levels. If the Level
 * has already been Initialized, it will not be recreated.
 *
 * @param name the name of the Level to initialize
 * @return a Exception of the initialization operation
 */
Exception *
InitializeLevelByName
( const char *name );

/**
 * @private
 * Creates the alert Level.
 *
 * @return the alert Level
 */
Level *
NewAlertLevel
( void );

/**
 * @private
 * Creates the critical Level.
 *
 * @return the critical Level
 */
Level *
NewCriticalLevel
( void );

/**
 * @private
 * Creates the debug Level.
 *
 * @return the debug Level
 */
Level *
NewDebugLevel
( void );

/**
 * @private
 * Creates the emergency Level.
 *
 * @return the emergency Level
 */
Level *
NewEmergencyLevel
( void );

/**
 * @private
 * Creates the error Level.
 *
 * @return the error Level
 */
Level *
NewErrorLevel
( void );

/**
 * @private
 * Creates the informational Level.
 *
 * @return the informational Level
 */
Level *
NewInformationalLevel
( void );

/**
 * @private
 * Creates the notice Level.
 *
 * @return the notice Level
 */
Level *
NewNoticeLevel
( void );

/**
 * @private
 * Creates the warning Level.
 *
 * @return the warning Level
 */
Level *
NewWarningLevel
( void );

#endif
