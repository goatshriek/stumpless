#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_TARGET_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_TARGET_H

#include "private/type.h"

TargetListIterator *
CopyTargetListIterator
( const TargetListIterator * );

void
DestroyTargetListIterator
( TargetListIterator * );

unsigned short
TargetListIteratorHasNext
( const TargetListIterator * );

TargetListIterator *
NewTargetListIterator
( TargetList *, int );

Target *
NextInTargetListIterator
( TargetListIterator * );

#endif
