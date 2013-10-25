#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <public_name.h>
#include <type.h>

void
__STUMPLESS_NAME( ListenForValues )
( __STUMPLESS_NAME( Logger ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ProcessValue )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ReceiveNextValue )
( __STUMPLESS_NAME( Logger ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SendValue )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Value ) * );

void
__STUMPLESS_NAME( UpdateStatus )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Status ) * );

#endif
