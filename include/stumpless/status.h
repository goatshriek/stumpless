#ifndef __STUMPLESS_STATUS_H
#define __STUMPLESS_STATUS_H

#include <stumpless/type.h>

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
RaiseAbnormalStatus
( const char * );

const char *
StatusToString
( Status * );

#endif
