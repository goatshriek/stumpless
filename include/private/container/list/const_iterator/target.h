#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_TARGET_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_TARGET_H

#include "private/type.h"

TargetListConstIterator *
CopyTargetListConstIterator
( const TargetListConstIterator * );

void
DestroyTargetListConstIterator
( TargetListConstIterator * );

unsigned short
TargetListConstIteratorHasNext
( const TargetListConstIterator * );

TargetListConstIterator *
NewTargetListConstIterator
( const TargetList *, int );

const Target *
NextInTargetListConstIterator
( TargetListConstIterator * );

#endif
