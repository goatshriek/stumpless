#ifndef __STUMPLESS_PRIVATE_RECORD_H
#define __STUMPLESS_PRIVATE_RECORD_H

#include "private/type.h"

char *
RecordToString
( Record * );

Record *
GetDebugRecord
( void );

Record *
RecordForEvent
( Event * );

Record *
GetErrorRecord
( void );

Record *
GetFatalRecord
( void );

Record *
GetInfoRecord
( void );

Record *
GetWarningRecord
( void );

Record *
MergeEntries
( Record *, Record * );

#endif
