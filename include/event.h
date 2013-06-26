#ifndef STUMPLESS_EVENT_H
#define STUMPLESS_EVENT_H

#include <public_name.h>
#include <type.h>

char *
__STUMPLESS_NAME( EventToString)( __STUMPLESS_NAME( Event ) * );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetDebugEvent )( void );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetErrorEvent )( void );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( EventForLevel )( __STUMPLESS_NAME( Level ) * );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetFatalEvent )( void );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetInfoEvent )( void );

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetWarningEvent )( void );

#endif
