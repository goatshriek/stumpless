#ifndef __STUMPLESS_FILTER_H
#define __STUMPLESS_FILTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFilter )
( __STUMPLESS_NAME( Filter ) * );

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( FindFilterByName )
( const char * );

void *
__STUMPLESS_NAME( GetFilterOption )
( const __STUMPLESS_NAME( Filter ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetFilterOption )
( __STUMPLESS_NAME( Filter ) *, const char *, void * );

#endif
