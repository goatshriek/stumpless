#ifndef __STUMPLESS_PRIVATE_TREE_H
#define __STUMPLESS_PRIVATE_TREE_H

#include "private/type.h"

Tree *
AddComparisonToDimension
( Dimension *, comparison_t );

Tree *
AddComparisonToTree
( Tree *, comparison_t );

Dimension *
AddDimensionToTree
( Tree *, const char * );

Tree *
AddToTree
( Tree *, void * );

Tree *
AddListToTree
( Tree *, List * );

void *
BeginDimension
( Dimension * );

void *
BeginTree
( Tree * );

Tree *
CopyTree
( Tree * );

void
DestroyDimension
( Dimension * );

void
DestroyTree
( Tree * );

Tree *
MergeTrees
( Tree *, Tree * );

void *
NextInTree
( Tree * );

Tree *
NewTree
();

Tree *
SetDimensionOptions
( Dimension *, Dictionary * );

Tree *
SetTreeDimension
( Tree *, Dimension * );

Tree *
SetTreeOptions
( Tree *, Dictionary * );

unsigned short
TreeContains
( Tree *, void * );

unsigned short
TreeIsEmpty
( Tree * );

#endif
