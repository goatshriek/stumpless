#ifndef __STUMPLESS_PRIVATE_LOGGER_SENDER_H
#define __STUMPLESS_PRIVATE_LOGGER_SENDER_H

#include "private/type.h"

Status *
SendLoggerStatus
( Logger *logger );

Status *
SendRecord
( Logger *, Record * );

#endif
