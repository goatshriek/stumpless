#ifndef __STUMPLESS_PRIVATE_FILTER_BASE_H
#define __STUMPLESS_PRIVATE_FILTER_BASE_H

#include "private/type.h"

unsigned short
EmptyFilterAcceptRecord
( const Filter *, const Record * );

unsigned short
EmptyFilterAcceptOutput
( const Filter *, const Output * );

unsigned short
EmptyFilterAcceptValue
( const Filter *, const Value * );

unsigned short
LevelFilterAcceptRecord
( const Filter *, const Record * );

unsigned short
LevelFilterAcceptOutput
( const Filter *, const Output * );

unsigned short
LevelFilterAcceptValue
( const Filter *, const Value * );

#endif
