#include <stdlib.h>

#include "private/status.h"
#include "private/type.h"

static Status * last_error = NULL;
static Status * last_failure = NULL;

Status *
AddStatus
( Status * status )
{
  return NULL;
}

Status *
FindStatusByName
( const char * name )
{
  return NULL;
}

Status *
InitializeStatus
( void )
{
  return NULL;
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

// todo remove
const char *
StatusToString( StatusCode code )
{
  switch( code ){
    case STUMPLESS_SUCCESS:
      return "no failures reported";
    case STUMPLESS_FAILURE:
      return "failure";
    case STUMPLESS_FILE_FAILURE:
      return "file operation failure";
    case STUMPLESS_FILE_READ_FAILURE:
      return "file read failure";
    case STUMPLESS_FILE_WRITE_FAILURE:
      return "file write failure";
    case STUMPLESS_FILE_OPEN_FAILURE:
      return "file open failure";
    case STUMPLESS_FILE_CLOSE_FAILURE:
      return "file close failure";
    case STUMPLESS_INCORRECT_FILE_SIGNATURE:
      return "file has incorrect signature";
    case STUMPLESS_MEMORY_ALLOCATION_FAILURE:
      return "memory allocation failure";
    case STUMPLESS_PARSE_FAILURE:
      return "parse failure";
    default:
      return NULL;
  }
}

