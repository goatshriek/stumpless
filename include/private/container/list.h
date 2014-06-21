#ifndef __STUMPLESS_PRIVATE_LIST_H
#define __STUMPLESS_PRIVATE_LIST_H

#include "private/type.h"

List *
AddSeparatorToList
( List *, void * );

List *
AppendLists
( List *, const List * );

List *
AppendToList
( List *, void * );

ListIterator *
BeginList
( List * );

ListConstIterator *
CBeginList
( const List * );

ListConstIterator *
CEndList
( const List * );

List *
CopyList
( const List * );

ListConstReverseIterator *
CRBeginList
( const List * );

ListConstReverseIterator *
CREndList
( const List * );

void
DestroyList
( List * );

ListIterator *
EndList
( List * );

void *
ListBack
( const List * );

unsigned short
ListContains
( const List *, const void * );

void *
ListFront
( const List * );

unsigned short
ListIsEmpty
( const List * );

unsigned
ListSize
( const List * );

List *
NewList
( void );

List *
PrependToList
( List *, void * );

ListReverseIterator *
RBeginList
( List * );

ListReverseIterator *
REndList
( List * );

#endif
