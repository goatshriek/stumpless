#ifndef STUMPLESS_PRIVATE_HANDLER_H
#define STUMPLESS_PRIVATE_HANDLER_H

#include "private/type.h"

Status *
AddHandler
( Handler * );

Handler *
FindHandlerByName
( const char * );

void *
GetHandlerOption
( const Handler *, const char * );

Status *
SetHandlerOption
( Handler *, const char *, void * );

#endif
