#ifndef __STUMPLESS_PRIVATE_CONFIGURATION_H
#define __STUMPLESS_PRIVATE_CONFIGURATION_H

#include <type.h>

__NAME( StatusCode )
__NAME( AddLoggingProfile )( __NAME( LoggingProfile ) * );

__NAME( StatusCode )
__NAME( AddOutputProfile )( __NAME( OutputProfile ) * );

__NAME( StatusCode )
__NAME( AddValueProfile )( __NAME( ValueProfile ) * );

__NAME( LoggingProfile ) *
__NAME( FindLoggingProfileByName )( const char * );

__NAME( OutputProfile ) *
__NAME( FindOutputProfileByName )( const char * );

__NAME( ValueProfile ) *
__NAME( FindValueProfileByName )( const char * );

__NAME( Configuration ) *
__NAME( GetConfiguration )( void );

__NAME( StatusCode )
__NAME( InitializeConfiguration )( void );

__NAME( StatusCode )
__NAME( InitializeLoggingProfiles )( void );

__NAME( StatusCode )
__NAME( InitializeOutputProfiles )( void );

__NAME( StatusCode )
__NAME( InitializeValueProfiles )( void );

__NAME( StatusCode )
__NAME( SetConfiguration )( __NAME( Configuration ) * );

#endif
