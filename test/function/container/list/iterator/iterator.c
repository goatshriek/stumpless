#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"
#include "private/container/list.h"
#include "private/container/list/iterator.h"
#include "private/type.h"
#include "static/container/list.h"
#include "static/container/list/iterator.h"

const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_has_next( void );
const char * test_has_previous( void );
const char * test_next( void );
const char * test_previous( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( has_next )
  RUN_TEST( has_previous )
  RUN_TEST( next )
  RUN_TEST( previous )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_constructor
( void )
{
  List * list = NULL;
  ListIterator * iterator = BeginList( list );
  FAIL_IF_NOT_NULL( iterator, "a null list returned a non-null iterator" )

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  iterator = BeginList( list );
  FAIL_IF_NULL( iterator, "a non-null list returned a null iterator" )

  if( iterator->list != list )
    return "the iterator did not have the appropriate list";
  if( iterator->current != list->first )
    return "the iterator did not start at the beginning of the list";

  return NULL;
}

const char *
test_copy
( void )
{
  ListIterator * iterator = NULL;
  ListIterator * copy = CopyListIterator( iterator );
  FAIL_IF_NOT_NULL( copy, "coyping a null iterator returned a non-null iterator" )

  iterator = BuildListIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )
  List * list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  Node * current = iterator->current;
  FAIL_IF_NULL( current, "the iterator did not start at the beginning of the list" )

  copy = CopyListIterator( iterator );
  FAIL_IF_NULL( copy, "copying a non-null iterator returned a null pointer" )
  if( copy->list != list )
    return "the copy did not point to the same list as the original";
  if( copy->current != current )
    return "the copy did not start in the same place as the original";

  return NULL;
}

const char *
test_destructor( void )
{
  ListIterator * iterator = NULL;
  DestroyListIterator( iterator );

  iterator = BuildListIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  List * list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  if( ListIsEmpty( list ) )
    return "the iterator's list was empty";

  DestroyListIterator( iterator );

  if( ListIsEmpty( list ) )
    return "the destruction of the iterator destroyed the list as well";

  return NULL;
}

const char *
test_has_next( void )
{
  if( ListIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  ListIterator *iterator = BuildListIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  while( iterator->current != NULL ){
    if( !ListIteratorHasNext( iterator ) )
      return "an iterator with a remaining value returned false";

    NextInListIterator( iterator );
  }

  if( ListIteratorHasNext( iterator ) )
    return "a finished iterator returned true";

  return NULL;
}

const char *
test_has_previous
( void )
{
  if( ListIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListIterator *iterator = BuildListIterator();
  if( !iterator )
    return "could not build the test iterator";
  if( ListIteratorHasPrevious( iterator ) )
    return "a new iterator had a previous value";
  if( !NextInListIterator( iterator ) )
    return "the iterator did not have any values";

  while( iterator->current != NULL ){
    if( !ListIteratorHasPrevious( iterator ) )
      return "an iterator that returned a value did not have a previous value";

    NextInListIterator( iterator );
  }

  if( !ListIteratorHasPrevious( iterator ) )
    return "a finished iterator did not have a previous value";

  return NULL;
}

const char *
test_next
( void )
{
  if( ListIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  ListIterator *iterator = BuildListIterator();
  if( !iterator )
    return "could not build the test iterator";

  Node *current;
  while( ListIteratorHasNext( iterator ) ){
    current = iterator->current;

    if( iterator->current->value != NextInListIterator( iterator ) )
      return "next did not return the placeholder value";

    if( iterator->current == current )
      return "the iterator placeholder was not advanced";
  }

  if( NextInListIterator( iterator ) )
    return "a finished iterator returned a non-null value";

  return NULL;
}

const char *
test_previous
( void )
{
  if( ListIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListIterator *iterator = BuildListIterator();
  if( !iterator )
    return "could not build the test iterator";

  void *previous = NextInListIterator( iterator );
  while( ListIteratorHasNext( iterator ) ){
    if( PreviousInListIterator( iterator ) != previous )
      return "calling previous did not return the previous value";

    NextInListIterator( iterator );
    previous = NextInListIterator( iterator );
  }

  return NULL;
}
