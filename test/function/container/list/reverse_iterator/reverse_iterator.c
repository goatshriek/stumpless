#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"
#include "private/container/list.h"
#include "private/container/list/reverse_iterator.h"
#include "private/type.h"
#include "static/container/list.h"
#include "static/container/list/reverse_iterator.h"

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
  ListReverseIterator *iterator = RBeginList( NULL );
  FAIL_IF_NOT_NULL( iterator, "a null list returned a non-null iterator" )

  List *list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  iterator = RBeginList( list );
  FAIL_IF_NULL( iterator, "a non-null list returned a null iterator" )

  if( iterator->list != list )
    return "the iterator did not have the appropriate list";
  if( iterator->current != list->last )
    return "the iterator did not start at the end of the list";

  return NULL;
}

const char *
test_copy
( void )
{
  ListReverseIterator *copy = CopyListReverseIterator( NULL );
  FAIL_IF_NOT_NULL( copy, "copying a null iterator returned a non-null iterator" )

  ListReverseIterator *iterator = BuildListReverseIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )
  List *list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  Node *current = iterator->current;
  FAIL_IF_NULL( current, "the iterator did not start at the end of the list" )

  copy = CopyListReverseIterator( iterator );
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
  DestroyListIterator( NULL );

  ListReverseIterator *iterator = BuildListReverseIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  List *list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  if( ListIsEmpty( list ) )
    return "the iterator's list was empty";

  DestroyListIterator( iterator );

  if( ListIsEmpty( list ) )
    return "the iterator's list was destroyed as well";

  return NULL;
}

const char *
test_has_next( void )
{
  if( ListReverseIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  ListReverseIterator *iterator = BuildListReverseIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  while( iterator->current ){
    if( !ListReverseIteratorHasNext( iterator ) )
      return "an iterator with a remaining value returned false";

    NextInListReverseIterator( iterator );
  }

  if( ListReverseIteratorHasNext( iterator ) )
    return "a finished iterator returned true";

  return NULL;
}

const char *
test_has_previous
( void )
{
  if( ListIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListReverseIterator *iterator = BuildListReverseIterator();
  if( !iterator )
    return "could not build the test iterator";
  if( ListIteratorHasPrevious( iterator ) )
    return "a new iterator had a previous value";
  if( !NextInListReverseIterator( iterator ) )
    return "the iterator did not have any values";

  while( iterator->current ){
    if( !ListIteratorHasPrevious( iterator ) )
      return "an iterator that returned a value did not have a previous value";

    NextInListReverseIterator( iterator );
  }

  if( !ListIteratorHasPrevious( iterator ) )
    return "a finished iterator did not have a previous value";

  return NULL;
}

const char *
test_next
( void )
{
  if( ListReverseIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  ListReverseIterator *iterator = BuildListReverseIterator();
  if( !iterator )
    return "could not build the test iterator";

  Node *current;
  while( ListReverseIteratorHasNext( iterator ) ){
    current = iterator->current;

    if( iterator->current->value != NextInListReverseIterator( iterator ) )
      return "next did not return the placeholder value";

    if( iterator->current == current )
      return "the iterator placeholder was not advanced";
  }

  if( NextInListReverseIterator( iterator ) )
    return "a finished iterator returned a non-null value";

  return NULL;
}

const char *
test_previous
( void )
{
  if( ListIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListReverseIterator *iterator = BuildListReverseIterator();
  if( !iterator )
    return "could not build the test iterator";

  void *previous = NextInListReverseIterator( iterator );
  while( ListReverseIteratorHasNext( iterator ) ){
    if( PreviousInListReverseIterator( iterator ) != previous )
      return "calling previous did not return the previous value";

    NextInListReverseIterator( iterator );
    previous = NextInListReverseIterator( iterator );
  }

  return NULL;
}
