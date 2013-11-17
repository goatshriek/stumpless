#ifndef STUMPLESS_PRIVATE_FILTER_BASE_H
#define STUMPLESS_PRIVATE_FILTER_BASE_H

#include "private/type.h"

unsigned short
EmptyFilterAcceptEntry
( Entry *, Dictionary * );

unsigned short
EmptyFilterAcceptOutput
( Output *, Dictionary *);

unsigned short
EmptyFilterAcceptValue
( Value *, Dictionary * );

unsigned short
LevelFilterAcceptEntry
( Entry *, Dictionary * );

unsigned short
LevelFilterAcceptOutput
( Output *, Dictionary * );

unsigned short
LevelFilterAcceptValue
( Value *, Dictionary * );

#endif
