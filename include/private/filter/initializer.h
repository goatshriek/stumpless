#ifndef __STUMPLESS_PRIVATE_FILTER_INITIALIZER_H
#define __STUMPLESS_PRIVATE_FILTER_INITIALIZER_H

#include "private/type.h"

Filter *
InitializeEmptyFilter
( void );

Exception *
InitializeFilterByName
( const char * );

Filter *
InitializeLevelFilter
( void );

#endif
