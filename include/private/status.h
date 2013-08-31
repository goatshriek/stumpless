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
InitializeStatus
( void );

Status *
GetLastError
( void );

Status *
GetLastFailure
( void );

// todo remove
const char *
StatusToString( StatusCode );

#endif
