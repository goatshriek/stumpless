#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/status/initializer.h"
#include "private/type.h"

static Dictionary *status_dictionary = NULL;

static Status *last_error = NULL; // function call failed due to bad parameters/information
static Status *last_failure = NULL; // function call failed due to internal error
static Status *last_warning = NULL; // function call succeeded with minor problem

Status *
AddStatus
( Status * status )
{
  if( !status || !status->name )
    return NULL;

  if( !status_dictionary ){
    status_dictionary = NewDictionary();

    if( !status_dictionary )
      return NULL;
  }

  void *value = ( void * ) status;
  if( !SetDictionaryValue( status_dictionary, status->name, value ) )
    return NULL;

  return status;
}

Status *
FindStatusByName
( const char *name )
{
  if( !status_dictionary )
    status_dictionary = NewDictionary();

  Status *status = GetDictionaryValue( status_dictionary, name );

  if( !status )
    status = InitializeStatusByName( name );

  return status;
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
RaiseStatus
( const char *name )
{
  Status *status = FindStatusByName( name );

  if( !status )
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
StatusToString( Status *status )
{
  if( !status )
    return NULL;
  else
    return status->name;
}

