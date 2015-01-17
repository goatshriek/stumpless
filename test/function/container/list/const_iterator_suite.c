#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list.h"
#include "private/container/list/const_iterator.h"
#include "private/type.h"
#include "static/container/list.h"
#include "static/container/list/const_iterator.h"
#include "test/helper.h"

const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_has_next( void );
//const char * test_has_previous( void );
const char * test_next( void );
//const char * test_previous( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( has_next )
  //RUN_TEST( has_previous )
  RUN_TEST( next )
  //RUN_TEST( previous )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_constructor
( void )
{
  const List *list;
  ListConstIterator *iterator;

  iterator = CBeginList( NULL );
  FAIL_IF_NOT_NULL( iterator, "a null list returned a non-null iterator" )

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  iterator = CBeginList( list );
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
  const List *list;
  ListConstIterator *copy, *iterator;
  Node *current;

  copy = CopyListConstIterator( NULL );
  FAIL_IF_NOT_NULL( copy, "copying a null iterator returned a non-null iterator" )

  iterator = BuildListConstIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )
  list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  current = iterator->current;
  FAIL_IF_NULL( current, "the iterator did not start at the beginning of the list" )

  copy = CopyListConstIterator( iterator );
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
  const List *list;
  ListConstIterator *iterator;

  DestroyListConstIterator( NULL );

  iterator = BuildListConstIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  list = iterator->list;
  FAIL_IF_NULL( list, "the iterator did not have a list" )
  if( ListIsEmpty( list ) )
    return "the iterator's list was empty";

  DestroyListConstIterator( iterator );

  if( ListIsEmpty( list ) )
    return "the list was destroyed as well";

  return NULL;
}

const char *
test_has_next( void )
{
  ListConstIterator *iterator;

  if( ListConstIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  iterator = BuildListConstIterator();
  FAIL_IF_NULL( iterator, "could not build the test iterator" )

  while( iterator->current ){
    if( !ListConstIteratorHasNext( iterator ) )
      return "an iterator with a remaining value returned false";

    NextInListConstIterator( iterator );
  }

  if( ListConstIteratorHasNext( iterator ) )
    return "a finished iterator returned true";

  return NULL;
}

/*const char *
test_has_previous
( void )
{
  if( ListConstIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListConstIterator *iterator = BuildListConstIterator();
  if( !iterator )
    return "could not build the test iterator";
  if( ListConstIteratorHasPrevious( iterator ) )
    return "a new iterator had a previous value";
  if( !NextInListConstIterator( iterator ) )
    return "the iterator did not have any values";

  while( iterator->current ){
    if( !ListConstIteratorHasPrevious( iterator ) )
      return "an iterator that returned a value did not have a previous value";

    NextInListConstIterator( iterator );
  }

  if( !ListConstIteratorHasPrevious( iterator ) )
    return "a finished iterator did not have a previous value";

  return NULL;
}*/

const char *
test_next
( void )
{
  ListConstIterator *iterator;
  Node *current;

  if( ListConstIteratorHasNext( NULL ) )
    return "a null iterator had a next value";

  iterator = BuildListConstIterator();
  if( !iterator )
    return "could not build the test iterator";

  while( ListConstIteratorHasNext( iterator ) ){
    current = iterator->current;

    if( iterator->current->value != NextInListConstIterator( iterator ) )
      return "next did not return the placeholder value";

    if( iterator->current == current )
      return "the iterator placeholder was not advanced";
  }

  if( NextInListConstIterator( iterator ) )
    return "a finished iterator returned a non-null value";

  return NULL;
}

/*const char *
test_previous
( void )
{
  if( ListConstIteratorHasPrevious( NULL ) )
    return "a null iterator had a previous value";

  ListConstIterator *iterator = BuildListConstIterator();
  if( !iterator )
    return "could not build the test iterator";

  const void *previous = NextInListConstIterator( iterator );
  while( ListConstIteratorHasNext( iterator ) ){
    if( PreviousInListConstIterator( iterator ) != previous )
      return "calling previous did not return the previous value";

    NextInListConstIterator( iterator );
    previous = NextInListConstIterator( iterator );
  }

  return NULL;
}*/
