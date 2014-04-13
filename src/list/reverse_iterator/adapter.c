#include "private/list/reverse_iterator.h"

#include "private/list/reverse_iterator/adapter.h"
#include "private/list/reverse_iterator/inheritance.h"

#include "static/list/adapter.h"

#include "static/list/reverse_iterator/adapter.h"

LIST_REVERSE_ITERATOR_HAS_NEXT( Adapter )

COPY_LIST_REVERSE_ITERATOR( Adapter )

DESTROY_LIST_REVERSE_ITERATOR( Adapter )

NEW_LIST_REVERSE_ITERATOR( Adapter )

NEXT_IN_LIST_REVERSE_ITERATOR( Adapter )
