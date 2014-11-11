#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <stumpless/type.h>

Status *
AppendAdapterToLogger
( Logger *, Adapter * );

Status *
AppendFormatterToLogger
( Logger *, Formatter * );

Status *
AppendHandlerToLogger
( Logger *, Handler * );

Status *
CheckLoggerStatus
( Logger * );

void
DestroyLogger
( Logger * );

void
Listen
( Logger * );

Logger *
NewLogger
( const char * );

Status *
ProcessRecord
( Logger *, Record * );

Record *
ReceiveNextRecord
( Logger * );

#endif
