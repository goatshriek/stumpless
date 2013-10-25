#include <logger.h>

#include "private/logger.h"

void
__STUMPLESS_NAME( ListenForValues )
( __STUMPLESS_NAME( Logger ) * logger )
{
  return ListenForValues( logger );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( ProcessValue )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Value ) * value )
{
  return ProcessValue( logger, value );
}

__STUMPLESS_NAME( Value ) *
__STUMPLESS_NAME( ReceiveNextValue )
( __STUMPLESS_NAME( Logger ) * logger )
{
  return ReceiveNextValue( logger );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SendValue )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Value ) * value )
{
  return SendValue( logger, value );
}

void
__STUMPLESS_NAME( UpdateStatus )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Status ) *status )
{
  return UpdateStatus( logger, status );
}
