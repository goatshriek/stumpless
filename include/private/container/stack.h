#ifndef __STUMPLESS_PRIVATE_CONTAINER_STACK_H
#define __STUMPLESS_PRIVATE_CONTAINER_STACK_H

#include "private/type.h"

/**
 * Creates a copy of the provided Stack.
 *
 * @param stack the Stack to copy
 *
 * @return a new Stack that is a copy of the original
 */
Stack *
CopyStack
( const Stack *stack );

/**
 * Destroys the provided Stack. Does not affect the data stored in the Stack.
 *
 * @param stack the Stack to destroy
 */
void
DestroyStack
( Stack *stack );

/**
 * Creates a new Stack.
 *
 * @return a new Stack
 */
Stack *
NewStack
( void );

/**
 * Gets the top element on the Stack without changing it. If there are no
 * elements in the Stack then NULL is returned. This is similar to PopFromStack
 * except that it does not remove the value from the Stack.
 *
 * @param stack the Stack to peek at
 *
 * @return the top element of the Stack
 */
void *
PeekAtStack
( const Stack *stack );

/**
 * Removes the top element from the Stack and returns it. If there are no
 * elements in the Stack then NULL is returned.
 *
 * @param stack the Stack to pop the element from
 *
 * @return the top element of the Stack
 */
void *
PopFromStack
( Stack *stack );

/**
 * Puts an element onto the top of the Stack. If the Stack or value are NULL
 * then no action is taken.
 *
 * @param stack the Stack to push on to
 * @param value the value to push onto the Stack
 *
 * @return the Stack that was pushed to, or NULL on failure
 */
Stack *
PushToStack
( Stack *stack, void *value );

/**
 * Checks a Stack to see if it's empty.
 *
 * @param stack the Stack to check
 *
 * @return a positive value if the Stack is empty, 0 otherwise
 */
unsigned short
StackIsEmpty
( const Stack *stack );

/**
 * Gets the number of elements on the Stack.
 *
 * @param stack the Stack to get the size of
 *
 * @return the number of elements in the Stack
 */
unsigned
StackSize
( const Stack *stack );

#endif
