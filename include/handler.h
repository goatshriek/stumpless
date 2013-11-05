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

void *
__STUMPLESS_NAME( GetHandlerOption )
( const __STUMPLESS_NAME( Handler ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetHandlerOption )
( __STUMPLESS_NAME( Handler ) *, const char *, void * );

#endif
