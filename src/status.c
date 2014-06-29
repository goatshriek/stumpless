#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/status_initializer.h"
#include "private/type.h"

static Dictionary * status_dictionary = NULL;

static Status * last_error = NULL;
static Status * last_failure = NULL;
static Status * last_warning = NULL;

Status *
AddStatus
( Status * status )
{
  if( status == NULL || status->name == NULL )
    return NULL;
  
  if( status_dictionary == NULL ){
    status_dictionary = NewDictionary();
    
    if( status_dictionary == NULL )
      return NULL;
  }
  
  void * value = ( void * ) status;
  if( SetDictionaryValue( status_dictionary, status->name, value ) == NULL )
    return NULL;
  
  return status;
}

Status *
FindStatusByName
( const char * name )
{
  if( status_dictionary == NULL )
    status_dictionary = NewDictionary();
  
  Status * status = GetDictionaryValue( status_dictionary, name );
  
  if( status == NULL ){
    status = InitializeStatusByName( name );
  
    if( status == NULL )
      return NULL;
  }
}

Status *
GetLastError
( void )
{
  return last_error;
}

Status *
GetLastFailure
( void )
{
  return last_failure;
}

Status *
GetLastWarning
( void )
{
  return last_warning;
}

Status *
RaiseAbnormalStatus
( const char * name )
{
  Status * status = FindStatusByName( name );
  
  if( status == NULL )
      return NULL;
  
  if( status->error )
    last_error = status;
  
  if( status->failure )
    last_failure = status;
  
  if( status->warning )
    last_warning = status;
  
  return status;
}

const char *
StatusToString( Status * status )
{
  if( status == NULL )
    return NULL;
  else
    return status->name;
}

