#include <stdlib.h>

#include <status.h>
#include <types.h>

const char *
StumplessStatusToString( StumplessStatusCode code )
{
  switch( code ){
    case STUMPLESS_SUCCESS:
      break;
    case STUMPLESS_FAILURE:
      break;
    case STUMPLESS_FILE_FAILURE:
      break;
    case STUMPLESS_FILE_READ_FAILURE:
      break;
    case STUMPLESS_FILE_WRITE_FAILURE:
      break;
    case STUMPLESS_FILE_OPEN_FAILURE:
      break;
    case STUMPLESS_FILE_CLOSE_FAILURE:
      break;
    case STUMPLESS_INCORRECT_FILE_SIGNATURE:
      break;
    case STUMPLESS_MEMORY_ALLOCATION_FAILURE:
      break;
    case STUMPLESS_PARSE_FAILURE:
      break;
    default:
      return NULL;
  }
  
  return NULL;
}

