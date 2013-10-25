#ifndef STUMPLESS_PRIVATE_LOGGER_H
#define STUMPLESS_PRIVATE_LOGGER_H

#include "private/type.h"

void
ListenForValues
( Logger * );

Status *
ProcessValue
( Logger *, Value * );

Value *
ReceiveNextValue
( Logger * );

Status *
SendValue
( Logger *, Value * );

void
UpdateStatus
( Logger *, Status * );

#endif
