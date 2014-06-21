#ifndef __STUMPLESS_ENTRY_H
#define __STUMPLESS_ENTRY_H

#include <stumpless/type.h>

char *
EntryToString
( Entry * );

Entry *
GetDebugEntry
( void );

Entry *
EntryForEvent
( Event * );

Entry *
GetErrorEntry
( void );

Entry *
GetFatalEntry
( void );

Entry *
GetInfoEntry
( void );

Entry *
GetWarningEntry
( void );

Entry *
MergeEntries
( Entry *, Entry * );

#endif
