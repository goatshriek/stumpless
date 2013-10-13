#ifndef __STUMPLESS_LOGGER_PROFILE_H
#define __STUMPLESS_LOGGER_PROFILE_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddLoggerProfile )
( __STUMPLESS_NAME( LoggerProfile ) * );

__STUMPLESS_NAME( LoggerProfile ) *
__STUMPLESS_NAME( FindLoggerProfileByName )
( const char * );

#endif
