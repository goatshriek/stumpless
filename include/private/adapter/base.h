#ifndef STUMPLESS_PRIVATE_ADAPTER_BASE_H
#define STUMPLESS_PRIVATE_ADAPTER_BASE_H

#include "private/type.h"

Entry *
ValueThroughContextAdapter
( Value *, Dictionary * );

Entry *
ValueThroughLevelAdapter
( Value *, Dictionary * );

#endif
