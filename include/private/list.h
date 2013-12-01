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

void *
BeginList
( List * );

List *
CopyList
( const List * );

void
DestroyList
( List * );

unsigned short
ListContains
( const List *, const void * );

unsigned short
ListIsEmpty
( const List * );

unsigned
ListSize
( const List * );

void *
NextInList
( List * );

List *
NewList
( void );

List *
PrependToList
( List *, void * );

#endif
