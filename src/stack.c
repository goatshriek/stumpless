#include <stdlib.h>

#include "private/stack.h"
#include "private/static/stack.h"
#include "private/type.h"

Stack *
CopyStack
( const Stack * stack )
{
  if( stack == NULL )
    return NULL;
  
  Stack * copy = malloc( sizeof( Stack ) );
  if( copy == NULL )
    return NULL;
  
  copy->capacity = stack->capacity;
  copy->values = malloc( sizeof( void * ) * copy->capacity );
  if( copy->values == NULL )
    return NULL;
  
  unsigned i;
  for( i = 0; i < stack->top; i++ )
    copy->values[i] = stack->values[i];
  
  copy->top = stack->top;
  
  return copy;
}

void
DestroyStack
( Stack * stack )
{
  if( stack == NULL )
    return;
  
  free( stack->values );
  free( stack );
  
  return;
}

Stack *
NewStack
( void )
{
  Stack * stack = malloc( sizeof( Stack ) );
  if( stack == NULL )
    return NULL;
  
  stack->capacity = 10;
  stack->values = malloc( sizeof( void * ) * stack->capacity );
  if( stack->values == NULL )
    return NULL;
  stack->top = 0;
  
  return stack;
}

void *
PeekAtStack
( const Stack * stack )
{
  if( stack == NULL || stack->top == 0 )
    return NULL;
  
  return stack->values[stack->top - 1];
}

void *
PopFromStack
( Stack * stack )
{
  if( stack == NULL || stack->top == 0 )
    return NULL;
  
  return stack->values[--stack->top];
}

Stack *
PushToStack
( Stack * stack, void * value )
{
  if( stack == NULL )
    return NULL;
  
  if( stack->top == stack->capacity )
    if( Resize( stack ) == NULL )
      return NULL;
  
  stack->values[stack->top++] = value;
  
  return stack;
}

unsigned short
StackIsEmpty
( const Stack * stack )
{
  return stack == NULL || stack->top == 0;
}

unsigned
StackSize
( const Stack * stack )
{
  if( stack == NULL )
    return 0;
  
  return stack->top;
}

static
Stack *
Resize
( Stack * stack )
{
  stack->capacity *= 2;
  
  void ** new_array = malloc( sizeof( void * ) * stack->capacity );
  if( new_array == NULL )
    return NULL;
  
  unsigned i;
  for( i = 0; i < stack->top; i++ )
    new_array[i] = stack->values[i];
  
  free( stack->values );
  stack->values = new_array;
  
  return stack;
}
