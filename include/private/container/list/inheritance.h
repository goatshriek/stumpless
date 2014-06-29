#ifndef __STUMPLESS_PRIVATE_LIST_INHERITANCE_H
#define __STUMPLESS_PRIVATE_LIST_INHERITANCE_H

#include <stdlib.h>

#include "private/container/list.h"
#include "private/type.h"

#define ADD_SEPARATOR_TO_LIST( type )                                          \
type##List *                                                                   \
AddSeparatorTo##type##List                                                     \
( type##List * list, type * value )                                            \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  if( !AddSeparatorToList( list->list, value ) )                               \
    return NULL;                                                               \
                                                                               \
  return list;                                                                 \
}

#define APPEND_LISTS( type )                                                   \
type##List *                                                                   \
Append##type##Lists                                                            \
( type##List * first, type##List * second )                                    \
{                                                                              \
  if( !first || !second )                                                      \
    return NULL;                                                               \
                                                                               \
  if( !AppendLists( first->list, second->list ) )                              \
    return NULL;                                                               \
                                                                               \
  return first;                                                                \
}

#define APPEND_TO_LIST( type )                                                 \
type##List *                                                                   \
AppendTo##type##List                                                           \
( type##List * list, type * value )                                            \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  if( !AppendToList( list->list, value ) )                                     \
    return NULL;                                                               \
                                                                               \
  return list;                                                                 \
}

#define BEGIN_LIST( type )                                                     \
type##ListIterator *                                                           \
Begin##type##List                                                              \
( type##List * list )                                                          \
{                                                                              \
  return New##type##ListIterator( list, 0 );                                   \
}

#define CBEGIN_LIST( type )                                                    \
type##ListConstIterator *                                                      \
CBegin##type##List                                                             \
( const type##List * list )                                                    \
{                                                                              \
  return New##type##ListConstIterator( list, 0 );                              \
}

#define CEND_LIST( type )                                                      \
type##ListConstIterator *                                                      \
CEnd##type##List                                                               \
( const type##List * list )                                                    \
{                                                                              \
  return New##type##ListConstIterator( list, -1 );                             \
}

#define COPY_LIST( type )                                                      \
type##List *                                                                   \
Copy##type##List                                                               \
( const type##List * list )                                                    \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  type##List * copy = malloc( sizeof( type##List ) );                          \
  if( !copy )                                                                  \
    return NULL;                                                               \
                                                                               \
  copy->list = CopyList( list->list );                                         \
  if( !copy->list )                                                            \
    return NULL;                                                               \
                                                                               \
  return copy;                                                                 \
}

#define CRBEGIN_LIST( type )                                                   \
type##ListConstReverseIterator *                                               \
CRBegin##type##List                                                            \
( const type##List * list )                                                    \
{                                                                              \
  return New##type##ListConstReverseIterator( list, 0 );                       \
}

#define CREND_LIST( type )                                                     \
type##ListConstReverseIterator *                                               \
CREnd##type##List                                                              \
( const type##List * list )                                                    \
{                                                                              \
  return New##type##ListConstReverseIterator( list, -1 );                      \
}

#define DESTROY_LIST( type )                                                   \
void                                                                           \
Destroy##type##List                                                            \
( type##List * list )                                                          \
{                                                                              \
  if( !list )                                                                  \
    return;                                                                    \
                                                                               \
  DestroyList( list->list );                                                   \
                                                                               \
  free( list );                                                                \
                                                                               \
  return;                                                                      \
}

#define END_LIST( type )                                                       \
type##ListIterator *                                                           \
End##type##List                                                                \
( type##List * list )                                                          \
{                                                                              \
  return New##type##ListIterator( list, -1 );                                  \
}

#define LIST_CONTAINS( type )                                                  \
unsigned short                                                                 \
type##ListContains                                                             \
( const type##List * list, const type * value )                                \
{                                                                              \
  if( !list )                                                                  \
    return 0;                                                                  \
                                                                               \
  return ListContains( list->list, value );                                    \
}

#define LIST_IS_EMPTY( type )                                                  \
unsigned short                                                                 \
type##ListIsEmpty                                                              \
( const type##List * list )                                                    \
{                                                                              \
  return !list || ListIsEmpty( list->list );                                   \
}

#define LIST_SIZE( type )                                                      \
unsigned                                                                       \
type##ListSize                                                                 \
( const type##List * list )                                                    \
{                                                                              \
  if( !list )                                                                  \
    return 0;                                                                  \
                                                                               \
  return ListSize( list->list );                                               \
}

#define NEW_LIST( type )                                                       \
type##List *                                                                   \
New##type##List                                                                \
()                                                                             \
{                                                                              \
  type##List * list = malloc( sizeof( type##List ) );                          \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  list->list = NewList();                                                      \
  if( !list->list )                                                            \
    return NULL;                                                               \
                                                                               \
  return list;                                                                 \
}

#define PREPEND_TO_LIST( type )                                                \
type##List *                                                                   \
PrependTo##type##List                                                          \
( type##List * list, type * value )                                            \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  if( !PrependToList( list->list, value ) )                                    \
    return NULL;                                                               \
                                                                               \
  return list;                                                                 \
}

#define RBEGIN_LIST( type )                                                    \
type##ListReverseIterator *                                                    \
RBegin##type##List                                                             \
( type##List * list )                                                          \
{                                                                              \
  return New##type##ListReverseIterator( list, 0 );                            \
}

#define REND_LIST( type )                                                      \
type##ListReverseIterator *                                                    \
REnd##type##List                                                               \
( type##List * list )                                                          \
{                                                                              \
  return New##type##ListReverseIterator( list, -1 );                           \
}

#endif
