#ifndef __STUMPLESS_VALUE_PROFILE_H
#define __STUMPLESS_VALUE_PROFILE_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddValueProfile )
( __STUMPLESS_NAME( ValueProfile ) * );

__STUMPLESS_NAME( ValueProfile ) *
__STUMPLESS_NAME( FindValueProfileByName )
( const char * );

#endif
