#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <stumpless/type.h>

Exception *
AppendAdapterToLogger
( Logger *, Adapter * );

Exception *
AppendFormatterToLogger
( Logger *, Formatter * );

Exception *
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

Exception *
ProcessRecord
( Logger *, Record * );

Record *
ReceiveNextRecord
( Logger * );

#endif
