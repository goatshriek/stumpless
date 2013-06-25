#include <stdlib.h>

#include <status.h>
#include <type.h>

static StumplessStatus * last_error = NULL;
static StumplessStatus * last_failure = NULL;

StumplessStatus *
StumplessAddStatus( StumplessStatus * )
{
  return NULL;
}

StumplessStatus *
StumplessFindStatusByName( const char * name )
{
  return NULL;
}

StumplessStatus *
StumplessInitializeStatus( void )
{
  return NULL;
}

StumplessStatus *
StumplessGetLastError( void )
{
  return last_error;
}

StumplessStatus *
StumplessGetLastFailure( void )
{
  return last_failure;
}

// todo remove
const char *
StumplessStatusToString( StumplessStatusCode code )
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

