#ifndef __STUMPLESS_PRIVATE_FILTER_H
#define __STUMPLESS_PRIVATE_FILTER_H

#include "private/type.h"

Exception *
AddFilter
( Filter * );

void
DestroyFilter
( Filter * );

Filter *
FindFilterByName
( const char * );

void *
GetFilterOption
( const Filter *, const char * );

Exception *
SetFilterOption
( Filter *, const char *, void * );

#endif
