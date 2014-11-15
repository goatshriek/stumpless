#ifndef __STUMPLESS_STATIC_CONTAINER_QUEUE_H
#define __STUMPLESS_STATIC_CONTAINER_QUEUE_H

#include "private/type.h"

struct Queue {
  unsigned back;
  unsigned capacity;
  void **elements;
  unsigned front;
};

#endif
