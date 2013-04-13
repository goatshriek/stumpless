#ifndef STUMPLESS_STATUS_H
#define STUMPLESS_STATUS_H

#include <stdlib.h>

#include <types.h>

#define NULL_ON_FAILURE( status )                                              \
if( (status) != STUMPLESS_SUCCESS ){                                           \
  return NULL;                                                                 \
}

#define STATUS_ON_FAILURE( status )                                            \
if( (status) != STUMPLESS_SUCCESS ){                                           \
  return status;                                                               \
}

const char * StumplessStatusToString( StumplessStatusCode );

#endif
