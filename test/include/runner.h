#ifndef STUMPLESS_TEST_INCLUDE_RUNNER_H
#define STUMPLESS_TEST_INCLUDE_RUNNER_H

#include <stdlib.h>

#include "private/string_helper.h"

#define RUN_TEST( test )                                                       \
result = test_##test();                                                        \
if( result != NULL ){                                                          \
  char * test_name = title_case( replace_char( #test, '_', ' ' ) );            \
  printf( "%s Test Failed: %s\n", test_name, result );                         \
  failure_count++;                                                             \
}

#endif
