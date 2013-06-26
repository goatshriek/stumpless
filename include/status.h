#ifndef __STUMPLESS_STATUS_H
#define __STUMPLESS_STATUS_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddStatus )( __STUMPLESS_NAME( Status ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( FindStatusByName )( const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( InitializeStatus )( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( GetLastError )( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( GetLastFailure )( void );

// todo remove
const char *
__STUMPLESS_NAME( StatusToString )( __STUMPLESS_NAME( StatusCode ) );

#endif
