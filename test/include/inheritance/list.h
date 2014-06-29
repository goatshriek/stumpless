#ifndef __STUMPLESS_TEST_INCLUDE_INHERITANCE_LIST_H
#define __STUMPLESS_TEST_INCLUDE_INHERITANCE_LIST_H

#include <stdlib.h>

// todo implement
#define TEST_ADD_SEPARATOR( type )                                             \
const char *                                                                   \
test_add_separator                                                             \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

// todo implement
#define TEST_APPEND( type )                                                    \
const char *                                                                   \
test_append                                                                    \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

#define TEST_APPEND_TO( type )                                                 \
const char *                                                                   \
test_append_to                                                                 \
( void )                                                                       \
{                                                                              \
  type##List *list = New##type##List();                                        \
  if( !list )                                                                  \
    return "the list was not created";                                         \
                                                                               \
  type *first = Build##type();                                                 \
  type *second = Build##type();                                                \
  type *third = Build##type();                                                 \
  type *fourth = Build##type();                                                \
                                                                               \
  type##List *result = AppendTo##type##List( list, first );                    \
  if( result != list )                                                         \
    return "the first member was not successfully added";                      \
                                                                               \
  result = AppendTo##type##List( list, second );                               \
  if( result != list )                                                         \
    return "the second member was not successfully added";                     \
                                                                               \
  result = AppendTo##type##List( list, third );                                \
  if( result != list )                                                         \
    return "the third member was not successfully added";                      \
                                                                               \
  result = AppendTo##type##List( list, fourth );                               \
  if( result != list )                                                         \
    return "the fourth member was not successfully added";                     \
                                                                               \
  type##ListIterator *iterator = Begin##type##List( list );                    \
  type *retrieved = NextIn##type##ListIterator( iterator );                    \
  if( !retrieved )                                                             \
    return "the list did not have any members";                                \
  if( retrieved != first )                                                     \
    return "the first member of the list was not the first appended";          \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a second member";                            \
  if( retrieved != second )                                                    \
    return "the second member of the list was not the second appended";        \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a third member";                             \
  if( retrieved != third )                                                     \
    return "the third member of the list was not the third appended";          \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a fourth member";                            \
  if( retrieved != fourth )                                                    \
    return "the fourth member of the list was not the fourth appended";        \
                                                                               \
  if( type##ListIteratorHasNext( iterator ) )                                  \
    return "the list had more members than were added";                        \
                                                                               \
  Destroy##type##List( list );                                                 \
  Destroy##type( first );                                                      \
  Destroy##type( second );                                                     \
  Destroy##type( third );                                                      \
  Destroy##type( fourth );                                                     \
  Destroy##type##ListIterator( iterator );                                     \
                                                                               \
  return NULL;                                                                 \
}

#define TEST_BEGIN( type )                                                     \
const char *                                                                   \
test_begin                                                                     \
( void )                                                                       \
{                                                                              \
  type##ListIterator *iterator = Begin##type##List( NULL );                    \
  if( iterator )                                                               \
    return "an iterator was created from a null list";                         \
                                                                               \
  type##List *list = New##type##List();                                        \
  if( !list )                                                                  \
    return "could not create a new list";                                      \
                                                                               \
  iterator = Begin##type##List( list );                                        \
  if( !iterator )                                                              \
    return "an iterator could not be built from a new list";                   \
  if( type##ListIteratorHasNext( iterator ) )                                  \
    return "a new list's iterator had a member";                               \
                                                                               \
  Destroy##type##List( list );                                                 \
  Destroy##type##ListIterator( iterator );                                     \
                                                                               \
  list = Build##type##List();                                                  \
  if( !list )                                                                  \
    return "could not build a test list";                                      \
                                                                               \
  iterator = Begin##type##List( list );                                        \
  if( !iterator )                                                              \
    return "an iterator could not be built from the test list";                \
  if( !type##ListIteratorHasNext( iterator ) )                                 \
    return "a full list's iterator had no members";                            \
                                                                               \
  Destroy##type##List( list );                                                 \
  Destroy##type##ListIterator( iterator );                                     \
                                                                               \
  return NULL;                                                                 \
}

// todo implement
#define TEST_CBEGIN( type )                                                    \
const char *                                                                   \
test_cbegin                                                                    \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

// todo implement
#define TEST_CEND( type )                                                      \
const char *                                                                   \
test_cend                                                                      \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

#define TEST_CONSTRUCTOR( type )                                               \
const char *                                                                   \
test_constructor                                                               \
( void )                                                                       \
{                                                                              \
  type##List *list = New##type##List();                                        \
                                                                               \
  if( !list )                                                                  \
    return "could not create a new list";                                      \
                                                                               \
  if( !type##ListIsEmpty( list ) )                                             \
    return "a newly created list was not empty";                               \
                                                                               \
  Destroy##type##List( list );                                                 \
                                                                               \
  return NULL;                                                                 \
}

#define TEST_CONTAINS( type )                                                  \
const char *                                                                   \
test_contains                                                                  \
( void )                                                                       \
{                                                                              \
  type##List *list = Build##type##List();                                      \
  if( !list )                                                                  \
    return "could not build a test list";                                      \
                                                                               \
  type##ListIterator *iterator = Begin##type##List( list );                    \
  if( !iterator )                                                              \
    return "an iterator could not be built from the test list";                \
                                                                               \
  type *retrieved = NextIn##type##ListIterator( iterator );                    \
  if( !retrieved )                                                             \
    return "could not retrieve the first member of the list";                  \
                                                                               \
  if( !type##ListContains( list, retrieved ) )                                 \
    return "the list did not contain the first member returned";               \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "could not retrieve the second member of the list";                 \
                                                                               \
  if( !type##ListContains( list, retrieved ) )                                 \
    return "the list did not contain the second member returned";              \
                                                                               \
  type *unlisted = Build##type();                                              \
  if( !unlisted )                                                              \
    return "could not build a test member";                                    \
  if( type##ListContains( list, unlisted ) )                                   \
    return "the list contained a member that was newly created";               \
  type##List *result = AppendTo##type##List( list, unlisted );                 \
  if( result != list )                                                         \
    return "could not add a new element to the list";                          \
  if( !type##ListContains( list, unlisted ) )                                  \
    return "the list did not contain a member after it was added";             \
                                                                               \
  Destroy##type( unlisted );                                                   \
  Destroy##type##List( list );                                                 \
                                                                               \
  return NULL;                                                                 \
}

#define TEST_COPY( type )                                                      \
const char *                                                                   \
test_copy                                                                      \
( void )                                                                       \
{                                                                              \
  type##List *copy = Copy##type##List( NULL );                                 \
  if( copy )                                                                   \
    return "a copy was returned of a null pointer";                            \
                                                                               \
  type##List *list = Build##type##List();                                      \
  if( !list )                                                                  \
    return "could not build a test list";                                      \
                                                                               \
  copy = Copy##type##List( list );                                             \
  if( !copy )                                                                  \
    return "a copy was not returned from a test list";                         \
  if( copy == list )                                                           \
    return "the copy was the same as the original";                            \
                                                                               \
  type##ListIterator *originals = Begin##type##List( list );                   \
  if( !originals )                                                             \
    return "an iterator could not be created for the original list";           \
  type##ListIterator *copies = Begin##type##List( copy );                      \
  if( !copies )                                                                \
    return "an iterator could not be created for the copied list";             \
                                                                               \
  type *original_member = NextIn##type##ListIterator( originals );             \
  type *copy_member = NextIn##type##ListIterator( copies );                    \
  while( original_member ){                                                    \
    if( original_member != copy_member )                                       \
      return "the copy did not point to the same members as the original";     \
    original_member = NextIn##type##ListIterator( originals );                 \
    copy_member = NextIn##type##ListIterator( copies );                        \
  }                                                                            \
                                                                               \
  Destroy##type##List( list );                                                 \
  Destroy##type##List( copy );                                                 \
  Destroy##type##ListIterator( originals );                                    \
  Destroy##type##ListIterator( copies );                                       \
                                                                               \
  return NULL;                                                                 \
}

// todo implement
#define TEST_CRBEGIN( type )                                                   \
const char *                                                                   \
test_crbegin                                                                   \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

// todo implement
#define TEST_CREND( type )                                                     \
const char *                                                                   \
test_crend                                                                     \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

#define TEST_DESTRUCTOR( type )                                                \
const char *                                                                   \
test_destructor                                                                \
( void )                                                                       \
{                                                                              \
  type##List *list = New##type##List();                                        \
  if( !list )                                                                  \
    return "could not create a new list";                                      \
  Destroy##type##List( list );                                                 \
                                                                               \
  list = Build##type##List();                                                  \
  if( !list )                                                                  \
    return "could not build a test list";                                      \
  Destroy##type##List( list );                                                 \
                                                                               \
  return NULL;                                                                 \
}

// todo implement
#define TEST_END( type )                                                       \
const char *                                                                   \
test_end                                                                       \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

#define TEST_IS_EMPTY( type )                                                  \
const char *                                                                   \
test_is_empty                                                                  \
( void )                                                                       \
{                                                                              \
  if( !type##ListIsEmpty( NULL ) )                                             \
    return "a null list was not deemed empty";                                 \
                                                                               \
  type##List *list = Build##type##List();                                      \
  if( !list )                                                                  \
    return "could not build a test list";                                      \
                                                                               \
  if( type##ListIsEmpty( list ) )                                              \
    return "a full list was deemed empty";                                     \
                                                                               \
  Destroy##type##List( list );                                                 \
                                                                               \
  return NULL;                                                                 \
}

#define TEST_PREPEND_TO( type )                                                \
const char *                                                                   \
test_prepend_to                                                                \
( void )                                                                       \
{                                                                              \
  type##List *list = New##type##List();                                        \
  if( !list )                                                                  \
    return "the list was not created";                                         \
                                                                               \
  type *first = Build##type();                                                 \
  type *second = Build##type();                                                \
  type *third = Build##type();                                                 \
  type *fourth = Build##type();                                                \
                                                                               \
  type##List *result = PrependTo##type##List( list, first );                   \
  if( result != list )                                                         \
    return "the first member was not successfully added";                      \
                                                                               \
  result = PrependTo##type##List( list, second );                              \
  if( result != list )                                                         \
    return "the second member was not successfully added";                     \
                                                                               \
  result = PrependTo##type##List( list, third );                               \
  if( result != list )                                                         \
    return "the third member was not successfully added";                      \
                                                                               \
  result = PrependTo##type##List( list, fourth );                              \
  if( result != list )                                                         \
    return "the fourth member was not successfully added";                     \
                                                                               \
  type##ListIterator *iterator = Begin##type##List( list );                    \
  type *retrieved = NextIn##type##ListIterator( iterator );                    \
  if( !retrieved )                                                             \
    return "the list did not have any members";                                \
  if( retrieved != fourth )                                                    \
    return "the first member of the list was not the last prepended";          \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a second member";                            \
  if( retrieved != third )                                                     \
    return "the second member of the list was not the third prepended";        \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a third member";                             \
  if( retrieved != second )                                                    \
    return "the third member of the list was not the second prepended";        \
                                                                               \
  retrieved = NextIn##type##ListIterator( iterator );                          \
  if( !retrieved )                                                             \
    return "the list did not have a fourth member";                            \
  if( retrieved != first )                                                     \
    return "the fourth member of the list was not the first prepended";        \
                                                                               \
  if( type##ListIteratorHasNext( iterator ) )                                  \
    return "the list had more members than were added";                        \
                                                                               \
  Destroy##type##List( list );                                                 \
  Destroy##type( first );                                                      \
  Destroy##type( second );                                                     \
  Destroy##type( third );                                                      \
  Destroy##type( fourth );                                                     \
  Destroy##type##ListIterator( iterator );                                     \
                                                                               \
  return NULL;                                                                 \
}

// todo implement
#define TEST_RBEGIN( type )                                                    \
const char *                                                                   \
test_rbegin                                                                    \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

// todo implement
#define TEST_REND( type )                                                      \
const char *                                                                   \
test_rend                                                                      \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

// todo implement
#define TEST_SIZE( type )                                                      \
const char *                                                                   \
test_size                                                                      \
( void )                                                                       \
{                                                                              \
  return NULL;                                                                 \
}

#endif
