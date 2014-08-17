#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_TARGET_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_TARGET_H

#include "private/type.h"

TargetListReverseIterator *
CopyTargetListReverseIterator
( const TargetListReverseIterator * );

void
DestroyTargetListReverseIterator
( TargetListReverseIterator * );

unsigned short
TargetListReverseIteratorHasNext
( const TargetListReverseIterator * );

TargetListReverseIterator *
NewTargetListReverseIterator
( TargetList *, int );

Target *
NextInTargetListReverseIterator
( TargetListReverseIterator * );

#endif
