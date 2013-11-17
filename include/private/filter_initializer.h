#ifndef STUMPLESS_PRIVATE_FILTER_INITIALIZER_H
#define STUMPLESS_PRIVATE_FILTER_INITIALIZER_H

#include "private/type.h"

Filter *
InitializeEmptyFilter
( void );

Status *
InitializeFilterByName
( const char * );

Filter *
InitializeLevelFilter
( void );

#endif
