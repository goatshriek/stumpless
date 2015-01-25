#ifndef __STUMPLESS_PRIVATE_LOGGER_SENDER_H
#define __STUMPLESS_PRIVATE_LOGGER_SENDER_H

#include "private/type.h"

Exception *
SendLoggerException
( Logger *logger );

Logger *
SendRecord
( Logger *, Record * );

#endif
