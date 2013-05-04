#ifndef STUMPLESS_TEST_INCLUDE_CHECKER_H
#define STUMPLESS_TEST_INCLUDE_CHECKER_H

#include <stdlib.h>

#define FAIL_IF_NOT_NULL( value, message )                                     \
if( value != NULL )                                                            \
  return message;

#define FAIL_IF_NULL( value, message )                                         \
if( value == NULL )                                                            \
  return message;

#endif
