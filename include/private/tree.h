#ifndef __STUMPLESS_PRIVATE_TREE_H
#define __STUMPLESS_PRIVATE_TREE_H

#include "private/type.h"

Tree *
AddComparisonToTree
( Tree *, comparison_t );

Tree *
AddComparisonToTreeDimension
( Tree *, comparison_t, dimension_t );

dimension_t
AddDimensionToTree
( Tree *, const char * );

Tree *
AddToTree
( Tree *, void * );

Tree *
AddListToTree
( Tree *, List * );

void *
BeginTree
( Tree * );

void *
BeginTreeDimension
( Tree *, dimension_t );

Tree *
CopyTree
( Tree * );

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
SetTreeDimension
( Tree *, dimension_t );

Tree *
SetTreeDimensionOptions
( Tree *, dimension_t, Dictionary * );

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
