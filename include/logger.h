#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogDebug )( const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogError )( const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogFatal )( const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogInfo )( const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogWarning )( const char * );

#endif
