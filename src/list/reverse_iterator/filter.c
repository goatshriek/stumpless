#include "private/list/reverse_iterator.h"

#include "private/list/reverse_iterator/filter.h"
#include "private/list/reverse_iterator/inheritance.h"

#include "static/list/filter.h"

#include "static/list/reverse_iterator/filter.h"

COPY_LIST_REVERSE_ITERATOR( Filter )

DESTROY_LIST_REVERSE_ITERATOR( Filter )

LIST_REVERSE_ITERATOR_HAS_NEXT( Filter )

NEW_LIST_REVERSE_ITERATOR( Filter )

NEXT_IN_LIST_REVERSE_ITERATOR( Filter )
