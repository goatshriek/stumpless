#ifndef __STUMPLESS_EVENT_H
#define __STUMPLESS_EVENT_H

#include <stumpless/type.h>

char *
EventToString
( Event * );

Event *
GetDebugEvent
( void );

Event *
GetErrorEvent
( void );

Event *
EventForLevel
( Level * );

Event *
GetFatalEvent
( void );

Event *
GetInfoEvent
( void );

Event *
GetWarningEvent
( void );

#endif
