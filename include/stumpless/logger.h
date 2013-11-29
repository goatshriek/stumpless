#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddAdapterToLogger )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFormatterToLogger )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Formatter ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddHandlerToLogger )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Handler ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CheckLoggerStatus )
( __STUMPLESS_NAME( Logger ) * );

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
__STUMPLESS_NAME( SendStatus )
( __STUMPLESS_NAME( Logger ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SendValue )
( __STUMPLESS_NAME( Logger ) *, __STUMPLESS_NAME( Value ) * );

#endif
