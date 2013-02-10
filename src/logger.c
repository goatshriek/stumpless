#include <stdlib.h>

#include <configuration.h>
#include <logger.h>

StumplessStatusCode
StumplessLogDebug( const char * message )
{
  StumplessStatusCode result = STUMPLESS_SUCCESS;
  
  if( stumpless_configuration == NULL )
    result = StumplessInitializeConfiguration();
  
  return result;
}

StumplessStatusCode
StumplessLogError( const char * message )
{
  StumplessStatusCode result = STUMPLESS_SUCCESS;
  
  if( stumpless_configuration == NULL )
    result = StumplessInitializeConfiguration();
  
  return result;
}

StumplessStatusCode
StumplessLogFatal( const char * message )
{
  StumplessStatusCode result = STUMPLESS_SUCCESS;
  
  if( stumpless_configuration == NULL )
    result = StumplessInitializeConfiguration();
  
  return result;
}

StumplessStatusCode
StumplessLogInfo( const char * message )
{
  StumplessStatusCode result = STUMPLESS_SUCCESS;
  
  if( stumpless_configuration == NULL )
    result = StumplessInitializeConfiguration();
  
  return result;
}

StumplessStatusCode
StumplessLogWarning( const char * message )
{
  StumplessStatusCode result = STUMPLESS_SUCCESS;
  
  if( stumpless_configuration == NULL )
    result = StumplessInitializeConfiguration();
  
  return result;
}
