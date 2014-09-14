#ifndef STUMPLESS_PRIVATE_ADAPTER_BASE_H
#define STUMPLESS_PRIVATE_ADAPTER_BASE_H

#include "private/type.h"

Record *
RecordThroughContextAdapter
( Record *, Dictionary * );

Record *
RecordThroughLevelAdapter
( Record *, Dictionary * );

#endif
