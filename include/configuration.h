#ifndef __STUMPLESS_PRIVATE_CONFIGURATION_H
#define __STUMPLESS_PRIVATE_CONFIGURATION_H

#include <type.h>

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddLoggingProfile )( __STUMPLESS_NAME( LoggingProfile ) * );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddOutputProfile )( __STUMPLESS_NAME( OutputProfile ) * );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddValueProfile )( __STUMPLESS_NAME( ValueProfile ) * );

__STUMPLESS_NAME( LoggingProfile ) *
__STUMPLESS_NAME( FindLoggingProfileByName )( const char * );

__STUMPLESS_NAME( OutputProfile ) *
__STUMPLESS_NAME( FindOutputProfileByName )( const char * );

__STUMPLESS_NAME( ValueProfile ) *
__STUMPLESS_NAME( FindValueProfileByName )( const char * );

__STUMPLESS_NAME( Configuration ) *
__STUMPLESS_NAME( GetConfiguration )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeConfiguration )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeLoggingProfiles )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeOutputProfiles )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeValueProfiles )( void );

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( SetConfiguration )( __STUMPLESS_NAME( Configuration ) * );

#endif
