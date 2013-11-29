#ifndef __STUMPLESS_PRIVATE_LIST_H
#define __STUMPLESS_PRIVATE_lIST_H

#include "private/type.h"

List *
AddSeparatorToList
( List *, void * );

List *
AppendLists
( List *, List * );

List *
AppendToList
( List *, void * );

void *
BeginList
( List * );

List *
CopyList
( List * );

void
DestroyList
( List * );

unsigned short
ListContains
( List *, void * );

unsigned short
ListIsEmpty
( List * );

void *
NextInList
( List * );

List *
NewList
();

List *
PrependToList
( List *, void * );

#endif
