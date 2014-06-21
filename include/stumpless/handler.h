#ifndef __STUMPLESS_HANDLER_H
#define __STUMPLESS_HANDLER_H

#include <stumpless/type.h>

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
