#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <stumpless/type.h>

Logger *
AppendAdapterToLogger
( Logger *, Adapter * );

Logger *
AppendFormatterToLogger
( Logger *, Formatter * );

Logger *
AppendHandlerToLogger
( Logger *, Handler * );

Exception *
CheckLoggerException
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

Logger *
ProcessRecord
( Logger *, Record * );

Record *
ReceiveNextRecord
( Logger * );

#endif
