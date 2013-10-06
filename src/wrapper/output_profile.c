#include <output_profile.h>

#include "private/output_profile.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddOutputProfile )
( __STUMPLESS_NAME( OutputProfile ) * profile )
{
  return AddOutputProfile( profile );
}

__STUMPLESS_NAME( OutputProfile ) *
__STUMPLESS_NAME( FindOutputProfileByName )
( const char * name )
{
  return FindOutputProfileByName( name );
}
