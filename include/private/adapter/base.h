#ifndef STUMPLESS_PRIVATE_ADAPTER_BASE_H
#define STUMPLESS_PRIVATE_ADAPTER_BASE_H

#include <stumpless/config.h>

#include "private/type.h"

Record *
RecordThroughContextAdapter
( const Adapter *, Record * );

Record *
RecordThroughLevelAdapter
( const Adapter *, Record * );

#ifdef __STUMPLESS_HAVE_TIME_H
Record *
RecordThroughTimeAdapter
( const Adapter *, Record *record );
#endif

#endif
