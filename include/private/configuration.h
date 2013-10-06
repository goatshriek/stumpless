#ifndef STUMPLESS_PRIVATE_CONFIGURATION_H
#define STUMPLESS_PRIVATE_CONFIGURATION_H

#include "private/type.h"

StatusCode
AddLoggingProfile( LoggingProfile * );

StatusCode
AddOutputProfile( OutputProfile * );

LoggingProfile *
FindLoggingProfileByName( const char * );

OutputProfile *
FindOutputProfileByName( const char * );

Configuration *
GetConfiguration
( void );

StatusCode
InitializeConfiguration( void );

StatusCode
InitializeLoggingProfiles( void );

StatusCode
InitializeOutputProfiles( void );

Status *
SetConfiguration
( Configuration * );

#endif
