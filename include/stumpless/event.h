#ifndef __STUMPLESS_EVENT_H
#define __STUMPLESS_EVENT_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

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
