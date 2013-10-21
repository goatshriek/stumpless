#ifndef STUMPLESS_PRIVATE_LIST_H
#define STUMPLESS_PRIVATE_lIST_H

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

List *
CopyList
( List * );

void
DestroyList
( List * );

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

void *
StartList
( List * );

#endif
