#ifndef __STUMPLESS_STATIC_STACK_H
#define __STUMPLESS_STATIC_STACK_H

#include <stdint.h>

#include "private/type.h"

struct Stack {
  unsigned capacity;
  unsigned top;
  void ** values;
};

static
Stack *
Resize
( Stack * );

#endif
