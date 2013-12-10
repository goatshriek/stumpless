#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/tree.h"
#include "private/tree_static.h"
#include "private/type.h"

Tree *
AddComparisonToTree
( Tree * tree, comparison_t comparison )
{
  return NULL;
}

Tree *
AddComparisonToTreeDimension
( Tree * tree, comparison_t comparison, dimension_t dimension )
{
  return NULL;
}

dimension_t
AddDimensionToTree
( Tree * tree, const char * name )
{
  return 0;
}

Tree *
AddToTree
( Tree * tree, void * value )
{
  return NULL;
}

Tree *
AddListToTree
( Tree * tree, List * list )
{
  return NULL;
}

void *
BeginTree
( Tree * tree )
{
  return NULL;
}

void *
BeginTreeDimension
( Tree * tree, dimension_t dimension )
{
  return NULL;
}

Tree *
CopyTree
( Tree * tree )
{
  return NULL;
}

void
DestroyTree
( Tree * tree )
{
  return;
}

Tree *
MergeTrees
( Tree * tree_1, Tree * tree_2 )
{
 return NULL;
}

void *
NextInTree
( Tree * tree )
{
  return NULL;
}

Tree *
NewTree
()
{
  return NULL;
}

Tree *
SetTreeDimension
( Tree * tree, dimension_t dimension )
{
  return NULL;
}

Tree *
SetTreeDimensionOptions
( Tree * tree, dimension_t dimension, Dictionary * options )
{
  return NULL;
}

Tree *
SetTreeOptions
( Tree * tree, Dictionary * options )
{
  return NULL;
}

unsigned short
TreeContains
( Tree * tree, void * value )
{
  return 0;
}

unsigned short
TreeIsEmpty
( Tree * tree )
{
  return 0;
}

static
void
DestroyDimension
( Dimension * dimension )
{
  return;
}

static
void
DestroyNode
( Node * node, intptr_t previous )
{
  return;
}
