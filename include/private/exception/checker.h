#ifndef __STUMPLESS_PRIVATE_EXCEPTION_CHECKER_H
#define __STUMPLESS_PRIVATE_EXCEPTION_CHECKER_H

#include <stdlib.h>

#define NULL_ON_FAILURE( exception )                                           \
if( (exception) ){                                                             \
  return NULL;                                                                 \
}

#define STATUS_ON_FAILURE( exception )                                         \
if( (exception) ){                                                             \
  return exception;                                                            \
}

#endif
