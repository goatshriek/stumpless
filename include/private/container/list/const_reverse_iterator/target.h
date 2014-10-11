#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_TARGET_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_TARGET_H

#include "private/type.h"

TargetListConstReverseIterator *
CopyTargetListConstReverseIterator
( const TargetListConstReverseIterator * );

void
DestroyTargetListConstReverseIterator
( TargetListConstReverseIterator * );

unsigned short
TargetListConstReverseIteratorHasNext
( const TargetListConstReverseIterator * );

TargetListConstReverseIterator *
NewTargetListConstReverseIterator
( const TargetList *, int );

const Target *
NextInTargetListConstReverseIterator
( TargetListConstReverseIterator * );

#endif
