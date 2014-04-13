#ifndef __STUMPLESS_PRIVATE_FILTER_BASE_H
#define __STUMPLESS_PRIVATE_FILTER_BASE_H

#include "private/type.h"

unsigned short
EmptyFilterAcceptEntry
( const Entry *, Dictionary * );

unsigned short
EmptyFilterAcceptOutput
( const Output *, Dictionary *);

unsigned short
EmptyFilterAcceptValue
( const Value *, Dictionary * );

unsigned short
LevelFilterAcceptEntry
( const Entry *, Dictionary * );

unsigned short
LevelFilterAcceptOutput
( const Output *, Dictionary * );

unsigned short
LevelFilterAcceptValue
( const Value *, Dictionary * );

#endif
