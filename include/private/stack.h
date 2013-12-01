#ifndef __STUMPLESS_PRIVATE_STACK_H
#define __STUMPLESS_PRIVATE_STACK_H

#include "private/type.h"

Stack *
CopyStack
( const Stack * );

void
DestroyStack
( Stack * );

Stack *
NewStack
( void );

void *
PeekAtStack
( const Stack * );

void *
PopFromStack
( Stack * );

Stack *
PushToStack
( Stack *, void * );

unsigned short
StackIsEmpty
( const Stack * );

unsigned
StackSize
( const Stack * );

#endif
