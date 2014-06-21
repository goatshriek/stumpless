#ifndef __STUMPLESS_FILTER_H
#define __STUMPLESS_FILTER_H

#include <stumpless/type.h>

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
