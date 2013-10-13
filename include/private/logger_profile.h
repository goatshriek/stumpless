#ifndef __STUMPLESS_PRIVATE_LOGGER_PROFILE_H
#define __STUMPLESS_PRIVATE_LOGGER_PROFILE_H

#include "private/type.h"

Status *
AddLoggerProfile
( LoggerProfile * );

LoggerProfile *
FindLoggerProfileByName
( const char * );

#endif
