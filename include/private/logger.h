#ifndef STUMPLESS_PRIVATE_LOGGER_H
#define STUMPLESS_PRIVATE_LOGGER_H

#include "private/type.h"

StatusCode
LogDebug
( const char * );

StatusCode
LogError
( const char * );

StatusCode
LogFatal
( const char * );

StatusCode
LogInfo
( const char * );

StatusCode
LogWarning
( const char * );

#endif
