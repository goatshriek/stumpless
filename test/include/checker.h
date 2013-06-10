#ifndef STUMPLESS_TEST_INCLUDE_CHECKER_H
#define STUMPLESS_TEST_INCLUDE_CHECKER_H

#include <stdlib.h>

#define FAIL_IF_NOT_NULL( value, message )                                     \
if( (value) != NULL ){                                                         \
  return (message);                                                            \
}

#define FAIL_IF_NULL( value, message )                                         \
if( (value) == NULL ){                                                         \
  return (message);                                                            \
}


#define ASSERT_STRINGS_EQUAL( expected, actual, message )                      \
if( actual == NULL ){                                                          \
  printf( "Expected: %s\nInstead was NULL\n", (expected) );                    \
  return (message);                                                            \
}                                                                              \
if( strcmp( (expected), (actual) ) != 0 ){                                     \
  printf( "Expected: %s\nInstead was: %s\n", (expected), (actual) );           \
  return (message);                                                            \
}

#endif
