#ifndef __STUMPLESS_PRIVATE_HANDLER_H
#define __STUMPLESS_PRIVATE_HANDLER_H

#include "private/type.h"

Status *
AddHandler
( Handler * );

Handler *
FindHandlerByName
( const char * );

#endif
