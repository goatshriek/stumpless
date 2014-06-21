#include "private/container/list/reverse_iterator.h"

#include "private/container/list/reverse_iterator/filter.h"
#include "private/container/list/reverse_iterator/inheritance.h"

#include "static/container/list/filter.h"

#include "static/container/list/reverse_iterator/filter.h"

COPY_LIST_REVERSE_ITERATOR( Filter )

DESTROY_LIST_REVERSE_ITERATOR( Filter )

LIST_REVERSE_ITERATOR_HAS_NEXT( Filter )

NEW_LIST_REVERSE_ITERATOR( Filter )

NEXT_IN_LIST_REVERSE_ITERATOR( Filter )
