#ifndef __STUMPLESS_VALUE_PROFILE_H
#define __STUMPLESS_VALUE_PROFILE_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddValueProfile )
( __STUMPLESS_NAME( ValueProfile ) * );

__STUMPLESS_NAME( ValueProfile ) *
__STUMPLESS_NAME( FindValueProfileByName )
( const char * );

#endif
