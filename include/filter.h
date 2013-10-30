#ifndef __STUMPLESS_FILTER_H
#define __STUMPLESS_FILTER_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFilter )
( __STUMPLESS_NAME( Filter ) * );

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( FindFilterByName )
( const char * );

#endif
