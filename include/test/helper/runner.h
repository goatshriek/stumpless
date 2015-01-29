#ifndef __STUMPLESS_TEST_INCLUDE_RUNNER_H
#define __STUMPLESS_TEST_INCLUDE_RUNNER_H

#include <stdlib.h>

#include "private/utility/string.h"

#define RUN_TEST( test )                                                       \
result = test_##test();                                                        \
if( result != NULL ){                                                          \
  char * test_name = get_title_case( replace_char( #test, '_', ' ' ) );        \
  printf( "%s Test Failed: %s\n", test_name, result );                         \
  failure_count++;                                                             \
}

#define TEST( test )                                                           \
result = Test##test();                                                         \
if( result ){                                                                  \
  printf( "Test%s Failed: %s\n", #test, result );                              \
  failure_count++;                                                             \
}

#endif
