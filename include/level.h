#ifndef __STUMPLESS_LEVEL_H
#define __STUMPLESS_LEVEL_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetAlertLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetCriticalLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetDebugLevel )
( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetEmergencyLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetErrorLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetFatalLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetInfoLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetNoticeLevel )( void );

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetWarningLevel )( void );

char *
__STUMPLESS_NAME( LevelToString )( __STUMPLESS_NAME( Level ) * );

#endif
