#ifndef __STUMPLESS_STATIC_CONTAINER_QUEUE_H
#define __STUMPLESS_STATIC_CONTAINER_QUEUE_H

#include "private/type.h"

/** a container providing Queue functionality */
struct Queue {
  size_t back; /**< the index of the back element + 1 */
  size_t capacity; /**< the max number of elements held */
  void **elements; /**< the elements */
  size_t front; /**< the index of the front element */
};

#endif
