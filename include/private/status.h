#ifndef STUMPLESS_PRIVATE_STATUS_H
#define STUMPLESS_PRIVATE_STATUS_H

#include "private/type.h"

Status *
AddStatus
( Status * );

Status *
FindStatusByName
( const char * );

Status *
GetLastError
( void );

Status *
GetLastFailure
( void );

Status *
GetLastWarning
( void );

Status *
RaiseStatus
( const char * );

const char *
StatusToString( Status * );

#endif
