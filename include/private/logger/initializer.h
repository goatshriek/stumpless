#ifndef __STUMPLESS_PRIVATE_LOGGER_INITIALIZER_H
#define __STUMPLESS_PRIVATE_LOGGER_INITIALIZER_H

#include "private/type.h"

Logger *
InitializeConsoleLogger
( void );

Logger *
InitializeErrorLogger
( void );

Status *
InitializeLoggerByName
( const char * );

#endif
