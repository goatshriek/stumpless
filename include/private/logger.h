#ifndef STUMPLESS_PRIVATE_LOGGER_H
#define STUMPLESS_PRIVATE_LOGGER_H

#include "private/type.h"

Status *
LogDebug
( const char * );

Status *
LogError
( const char * );

Status *
LogFatal
( const char * );

Status *
LogInfo
( const char * );

Status *
LogWarning
( const char * );

#endif
