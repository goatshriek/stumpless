#ifndef STUMPLESS_TEST_INCLUDE_RUNNER_H
#define STUMPLESS_TEST_INCLUDE_RUNNER_H

#include <stdlib.h>

#define RUN_TEST( test, fail_message )                                         \
result = test();                                                               \
if( result != NULL ){                                                          \
  printf( fail_message, result );                                              \
  failure_count++;                                                             \
}

#endif
