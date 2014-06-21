#ifndef __STUMPLESS_LEVEL_H
#define __STUMPLESS_LEVEL_H

#include <stumpless/type.h>

Level *
GetAlertLevel
( void );

Level *
GetCriticalLevel
( void );

Level *
GetDebugLevel
( void );

Level *
GetEmergencyLevel
( void );

Level *
GetErrorLevel
( void );

Level *
GetFatalLevel
( void );

Level *
GetInfoLevel
( void );

Level *
GetNoticeLevel
( void );

Level *
GetWarningLevel
( void );

char *
LevelToString
( Level * );

#endif
