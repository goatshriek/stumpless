#ifndef __STUMPLESS_OUTPUT_PROFILE_H
#define __STUMPLESS_OUTPUT_PROFILE_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddOutputProfile )
( __STUMPLESS_NAME( OutputProfile ) * );

__STUMPLESS_NAME( OutputProfile ) *
__STUMPLESS_NAME( FindOutputProfileByName )
( const char * );

#endif
