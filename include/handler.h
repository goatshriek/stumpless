#ifndef __STUMPLESS_HANDLER_H
#define __STUMPLESS_HANDLER_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddHandler )
( __STUMPLESS_NAME( Handler ) * );

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( FindHandlerByName )
( const char * );

#endif
