#ifndef STUMPLESS_LEVEL_H
#define STUMPLESS_LEVEL_H

#include <type.h>

StumplessLevel *
StumplessGetAlertLevel( void );

StumplessLevel *
StumplessGetCriticalLevel( void );

StumplessLevel *
StumplessGetDebugLevel( void );

StumplessLevel *
StumplessGetEmergencyLevel( void );

StumplessLevel *
StumplessGetErrorLevel( void );

StumplessLevel *
StumplessGetFatalLevel( void );

StumplessLevel *
StumplessGetInfoLevel( void );

StumplessLevel *
StumplessGetNoticeLevel( void );

StumplessLevel *
StumplessGetWarningLevel( void );

char *
StumplessLevelToString( StumplessLevel * );

#endif
