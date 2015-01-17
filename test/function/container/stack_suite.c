#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/stack.h"
#include "private/type.h"
#include "static/container/stack.h"
#include "test/helper.h"

const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_peek( void );
const char * test_pop( void );
const char * test_push( void );
const char * test_resize( void );
const char * test_size( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( is_empty )
  RUN_TEST( peek )
  RUN_TEST( pop )
  RUN_TEST( push )
  RUN_TEST( resize )
  RUN_TEST( size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_constructor
( void )
{
  Stack * stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )

  FAIL_IF_NULL( stack->values, "the stack did not have a value array" )

  if( StackSize( stack ) != 0 )
    return "a new stack contained values";

  return NULL;
}

const char *
test_copy
( void )
{
  Stack *copy, *stack;

  copy = CopyStack( NULL );
  FAIL_IF_NOT_NULL( copy, "a copy of a NULL stack was not NULL" )

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build the test stack" )

  copy = CopyStack( stack );
  FAIL_IF_NULL( copy, "a full stack could not be copied" )

  if( stack->values == copy->values )
    return "the copy did not actually have a new list of values";

  if( stack->values[0] != copy->values[0] )
    return "the copy did not have the same first value";

  if( stack->values[1] != copy->values[1] )
    return "the copy did not have the same second value";

  if( stack->values[2] != copy->values[2] )
    return "the copy did not have the same third value";

  return NULL;
}

const char *
test_destructor
( void )
{
  Stack *stack;

  DestroyStack( NULL );

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" );

  DestroyStack( stack );

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build a full stack" )

  DestroyStack( stack );

  return NULL;
}

const char *
test_is_empty
( void )
{
  Stack *stack;

  if( !StackIsEmpty( NULL ) )
    return "a NULL stack was not empty";

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )

  if( !StackIsEmpty( stack ) )
    return "a new stack was not empty";

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build a full stack" )

  if( StackIsEmpty( stack ) )
    return "a full stack was deemed empty";

  return NULL;
}

const char *
test_peek
( void )
{
  Stack *stack;
  void *value;

  value = PeekAtStack( NULL );
  FAIL_IF_NOT_NULL( value, "a peek at a NULL stack was not NULL" )

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )
  value = PeekAtStack( stack );
  FAIL_IF_NOT_NULL( value, "a peek at an empty stack was not NULL" )

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build a full stack" )

  value = PeekAtStack( stack );
  FAIL_IF_NULL( value, "could not peek at a full stack" )
  ASSERT_STRINGS_EQUAL( "top", value, "the peek was not what was expected" )

  if( PeekAtStack( stack ) != value )
    return "a second peek did not return the same value";

  return NULL;
}

const char *
test_pop
( void )
{
  Stack *stack;
  void *peek, *value;

  value = PopFromStack( NULL );
  FAIL_IF_NOT_NULL( value, "a value popped from a NULL stack was not NULL" )

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )
  value = PopFromStack( stack );
  FAIL_IF_NOT_NULL( value, "a value popped from a new stack was not NULL" )
  value = PopFromStack( stack );
  FAIL_IF_NOT_NULL( value, "a value popped from a new stack twice was not NULL" )

  if( PushToStack( stack, "sucka" ) == NULL )
    return "could not push to the stack";
  value = PopFromStack( stack );
  FAIL_IF_NULL( value, "a value could not be popped from a stack" )
  ASSERT_STRINGS_EQUAL( "sucka", value, "the popped value was not what was previously pushed" )
  value = PopFromStack( stack );
  FAIL_IF_NOT_NULL( value, "a value was popped from a newly-emptied stack" )

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build a full stack" )

  peek = PeekAtStack( stack );
  value = PopFromStack( stack );
  if( value != peek )
    return "the popped value was not what was peeked at";

  return NULL;
}

const char *
test_push
( void )
{
  Stack *result, *stack;
  void *value;

  result = PushToStack( NULL, "this" );
  FAIL_IF_NOT_NULL( result, "pushing to a NULL stack did not return a NULL" )

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )

  result = PushToStack( stack, "this" );
  if( result != stack )
    return "could not push to a new stack";

  result = PushToStack( stack, "is" );
  if( result != stack )
    return "could not push to a stack with one element";

  result = PushToStack( stack, "old" );
  if( result != stack )
    return "could not push to a stack with two element";

  PopFromStack( stack );

  result = PushToStack( stack, "new" );
  if( result != stack )
    return "could not push onto a recently popped stack";

  value = PeekAtStack( stack );
  ASSERT_STRINGS_EQUAL( "new", value, "the top value was not what was last pushed" )

  return NULL;
}

const char *
test_resize
( void )
{
  Stack *result, *stack;
  unsigned i, previous_capacity;
  void *top;

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )

  previous_capacity = stack->capacity;
  for( i = 0; i < previous_capacity; i++ ){
    if( PushToStack( stack, "sucka" ) == NULL )
      return "could not push extra values onto a stack";
  }

  result = PushToStack( stack, "last straw" );
  if( result != stack )
    return "the stack could not be resized";

  if( previous_capacity * 2 != stack->capacity )
    return "the capacity was not actually doubled";

  top = PeekAtStack( stack );
  ASSERT_STRINGS_EQUAL( "last straw", top, "the values were not copied to the new value array" )

  return NULL;
}

const char *
test_size
( void )
{
  Stack *stack;
  unsigned size;

  size = StackSize( NULL );
  if( size != 0 )
    return "a NULL stack had a size greater than 0";

  stack = NewStack();
  FAIL_IF_NULL( stack, "could not build a new stack" )
  size = StackSize( stack );
  if( size != 0 )
    return "a new stack had a size greater than 0";

  stack = BuildStackOfStrings();
  FAIL_IF_NULL( stack, "could not build a full stack" )
  size = StackSize( stack );
  if( size != 3 )
    return "a full stack did not have the correct size";

  return NULL;
}
