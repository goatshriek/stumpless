#ifndef __STUMPLESS_PRIVATE_LOGGER_H
#define __STUMPLESS_PRIVATE_LOGGER_H

#include "private/type.h"

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
ProcessValue
( Logger *, Value * );

Value *
ReceiveNextValue
( Logger * );

Status *
SendLoggerStatus
( Logger * );

#endif
