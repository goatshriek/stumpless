#include <value_profile.h>

#include "private/value_profile.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddValueProfile )
( __STUMPLESS_NAME( ValueProfile ) * profile )
{
  return AddValueProfile( profile );
}

__STUMPLESS_NAME( ValueProfile ) *
__STUMPLESS_NAME( FindValueProfileByName )
( const char * name )
{
  return FindValueProfileByName( name );
}
