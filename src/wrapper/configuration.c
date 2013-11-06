#include "stumpless/configuration.h"

#include "private/configuration.h"

__STUMPLESS_NAME( Configuration ) *
__STUMPLESS_NAME( GetConfiguration )( void )
{
  return GetConfiguration();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( InitializeConfiguration )( void )
{
  return InitializeConfiguration();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetConfiguration )
( __STUMPLESS_NAME( Configuration ) * configuration )
{
  return SetConfiguration( configuration );
}
