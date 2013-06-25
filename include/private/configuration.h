#ifndef STUMPLESS_PRIVATE_CONFIGURATION_H
#define STUMPLESS_PRIVATE_CONFIGURATION_H

#include "private/type.h"

StatusCode
AddLoggingProfile( LoggingProfile * );

StatusCode
AddOutputProfile( OutputProfile * );

StatusCode
AddValueProfile( ValueProfile * );

LoggingProfile *
FindLoggingProfileByName( const char * );

OutputProfile *
FindOutputProfileByName( const char * );

ValueProfile *
FindValueProfileByName( const char * );

Configuration *
GetConfiguration( void );

StatusCode
InitializeConfiguration( void );

StatusCode
InitializeLoggingProfiles( void );

StatusCode
InitializeOutputProfiles( void );

StatusCode
InitializeValueProfiles( void );

StatusCode
SetConfiguration( Configuration * );

#endif
