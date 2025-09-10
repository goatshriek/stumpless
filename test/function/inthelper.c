// test/function/inthelper.c
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "private/inthelper.h"

// Prevent constant folding: make sure values are computed at runtime
static size_t runtime_size_t(size_t v) {
  volatile size_t x = v;
  return x;
}

static int check_cap_within(void) {
  size_t v = runtime_size_t((size_t)INT_MAX - 10);
  int r = cap_size_t_to_int(v);
  return r == (int)v ? 0 : 1;
}

static int check_cap_overflow(void) {
#if SIZE_MAX > INT_MAX
  size_t v = runtime_size_t((size_t)INT_MAX + 1);
  int r = cap_size_t_to_int(v);
  return r == INT_MAX ? 0 : 1;
#else
  size_t v = runtime_size_t((size_t)INT_MAX);
  int r = cap_size_t_to_int(v);
  return r == INT_MAX ? 0 : 1;
#endif
}

static int check_conv_within(void) {
  size_t v = runtime_size_t(12345u);
  int r = size_t_to_int(v);
  return r == 12345 ? 0 : 1;
}

static int check_conv_overflow(void) {
#if SIZE_MAX > INT_MAX
  size_t v = runtime_size_t((size_t)INT_MAX + 1);
  int r = size_t_to_int(v);
  return r == -1 ? 0 : 1;
#else
  size_t v = runtime_size_t((size_t)INT_MAX);
  int r = size_t_to_int(v);
  return r == INT_MAX ? 0 : 1;
#endif
}

int main(void) {
  int fails = 0;
  fails += check_cap_within();
  fails += check_cap_overflow();
  fails += check_conv_within();
  fails += check_conv_overflow();

  if (fails) {
    fprintf(stderr, "inthelper tests failed: %d\n", fails);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
