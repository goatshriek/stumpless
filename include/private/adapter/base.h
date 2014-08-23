#ifndef STUMPLESS_PRIVATE_ADAPTER_BASE_H
#define STUMPLESS_PRIVATE_ADAPTER_BASE_H

#include "private/type.h"

Entry *
EntryThroughContextAdapter
( Entry *, Dictionary * );

Entry *
EntryThroughLevelAdapter
( Entry *, Dictionary * );

#endif
