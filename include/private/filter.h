#ifndef __STUMPLESS_PRIVATE_FILTER_H
#define __STUMPLESS_PRIVATE_FILTER_H

#include "private/type.h"

Status *
AddFilter
( Filter * );

Filter *
FindFilterByName
( const char * );

#endif
