#ifndef __STUMPLESS_PRIVATE_HANDLER_H
#define __STUMPLESS_PRIVATE_HANDLER_H

#include "private/type.h"

Handler *
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

const Handler *
HandleOutput
( const Handler *, const Output * );

Handler *
SetHandlerOption
( Handler *, const char *, void * );

#endif
