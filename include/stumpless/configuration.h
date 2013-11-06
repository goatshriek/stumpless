#ifndef __STUMPLESS_PRIVATE_CONFIGURATION_H
#define __STUMPLESS_PRIVATE_CONFIGURATION_H

#include <stumpless/type.h>

__STUMPLESS_NAME( Configuration ) *
__STUMPLESS_NAME( GetConfiguration )
( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( InitializeConfiguration )
( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetConfiguration )
( __STUMPLESS_NAME( Configuration ) * );

#endif
