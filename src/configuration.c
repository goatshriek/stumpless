#include <configuration.h>
#include <types.h>

StumplessConfiguration * configuration = NULL;

StumplessConfiguration *
StumplessGetConfiguration( void )
{
  return configuration;
}

StumplessStatusCode
StumplessInitializeConfiguration( void )
{
  return STUMPLESS_SUCCESS;
}
