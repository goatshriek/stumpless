#ifndef STUMPLESS_PRIVATE_CONFIGURATION_H
#define STUMPLESS_PRIVATE_CONFIGURATION_H

#include "private/type.h"

StatusCode
AddLoggingProfile( LoggingProfile * );

LoggingProfile *
FindLoggingProfileByName( const char * );

Configuration *
GetConfiguration
( void );

StatusCode
InitializeConfiguration( void );

StatusCode
InitializeLoggingProfiles( void );

Status *
SetConfiguration
( Configuration * );

#endif
