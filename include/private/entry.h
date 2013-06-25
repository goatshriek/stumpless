#ifndef STUMPLESS_PRIVATE_ENTRY_H
#define STUMPLESS_PRIVATE_ENTRY_H

#include "private/type.h"

char *
EntryToString( Entry * );

Entry *
GetDebugEntry( void );

Entry *
EntryForEvent( Event * );

Entry *
GetErrorEntry( void );

Entry *
GetFatalEntry( void );

Entry *
GetInfoEntry( void );

Entry *
GetWarningEntry( void );

#endif
