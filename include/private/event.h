#ifndef STUMPLESS_EVENT_H
#define STUMPLESS_EVENT_H

#include "private/type.h"

char *
EventToString( Event * );

Event *
GetDebugEvent( void );

Event *
GetErrorEvent( void );

Event *
EventForLevel( Level * );

Event *
GetFatalEvent( void );

Event *
GetInfoEvent( void );

Event *
GetWarningEvent( void );

#endif
