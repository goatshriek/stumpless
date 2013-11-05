#ifndef STUMPLESS_PRIVATE_FILTER_H
#define STUMPLESS_PRIVATE_FILTER_H

#include "private/type.h"

Status *
AddFilter
( Filter * );

Filter *
FindFilterByName
( const char * );

void *
GetFilterOption
( const Filter *, const char * );

Status *
SetFilterOption
( Filter *, const char *, void * );

#endif
