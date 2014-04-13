#include "stumpless/logger.h"

#include "private/logger.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendAdapterToLogger )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Adapter ) * adapter )
{
  return AppendAdapterToLogger( logger, adapter );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendFormatterToLogger )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Formatter ) * formatter )
{
  return AppendFormatterToLogger( logger, formatter );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendHandlerToLogger )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Handler ) * handler )
{
  return AppendHandlerToLogger( logger, handler );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CheckLoggerStatus )
( __STUMPLESS_NAME( Logger ) * logger )
{
  return CheckLoggerStatus( logger );
}

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
__STUMPLESS_NAME( SendLoggerStatus )
( __STUMPLESS_NAME( Logger ) * logger )
{
  return SendLoggerStatus( logger );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SendValue )
( __STUMPLESS_NAME( Logger ) * logger, __STUMPLESS_NAME( Value ) * value )
{
  return SendValue( logger, value );
}
