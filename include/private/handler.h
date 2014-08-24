#ifndef __STUMPLESS_PRIVATE_HANDLER_H
#define __STUMPLESS_PRIVATE_HANDLER_H

#include "private/type.h"

Status *
AddHandler
( Handler * );

void
DestroyHandler
( Handler * );

Handler *
FindHandlerByName
( const char * );

void *
GetHandlerOption
( const Handler *, const char * );

Status *
HandleOutput
( const Handler *, const Output * );

Status *
SetHandlerOption
( Handler *, const char *, void * );

#endif
