#ifndef __STUMPLESS_PRIVATE_HANDLER_H
#define __STUMPLESS_PRIVATE_HANDLER_H

#include "private/type.h"

Exception *
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

Exception *
HandleOutput
( const Handler *, const Output * );

Exception *
SetHandlerOption
( Handler *, const char *, void * );

#endif
