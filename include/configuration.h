#ifndef __STUMPLESS_PRIVATE_CONFIGURATION_H
#define __STUMPLESS_PRIVATE_CONFIGURATION_H

#include <type.h>

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddLoggingProfile )( __STUMPLESS_NAME( LoggingProfile ) * );

__STUMPLESS_NAME( LoggingProfile ) *
__STUMPLESS_NAME( FindLoggingProfileByName )( const char * );

__STUMPLESS_NAME( Configuration ) *
__STUMPLESS_NAME( GetConfiguration )
( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeConfiguration )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeLoggingProfiles )( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetConfiguration )
( __STUMPLESS_NAME( Configuration ) * );

#endif
