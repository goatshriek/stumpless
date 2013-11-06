#ifndef STUMPLESS_STATUS_CHECKER_H
#define STUMPLESS_STATUS_CHECKER_H

#include <stdlib.h>

#define NULL_ON_FAILURE( status )                                              \
if( (status) != NULL ){                                                        \
  return NULL;                                                                 \
}

#define STATUS_ON_FAILURE( status )                                            \
if( (status) != NULL ){                                                        \
  return status;                                                               \
}

#endif
