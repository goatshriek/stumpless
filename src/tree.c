#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/tree.h"
#include "private/tree_static.h"
#include "private/type.h"

Tree *
AddComparisonToDimension
( Dimension * dimension, comparison_t comparison )
{
  return NULL;
}

Tree *
AddComparisonToTree
( Tree * tree, comparison_t comparison )
{
  return NULL;
}

Dimension *
AddDimensionToTree
( Tree * tree, const char * name )
{
  return NULL;
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
BeginDimension
( Dimension * dimension )
{
  return NULL;
}

void *
BeginTree
( Tree * tree )
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
DestroyDimension
( Dimension * dimension )
{
  return;
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
  Tree * tree = malloc( sizeof( Tree ) );
  if( tree == NULL )
    return NULL;
  
  tree->dimensions = NewList();
  if( tree->dimensions == NULL )
    return NULL;
  
  Dimension * dimension = malloc( sizeof( Dimension ) );
  if( dimension == NULL )
    return NULL;
  
  if( AppendToList( tree->dimensions, dimension ) != NULL )
    return NULL;
  
  tree->current_dimension = 0;
  tree->options = NULL;
  
  dimension->comparisons = NULL;
  dimension->index = 0;
  dimension->name = NULL;
  dimension->options = NULL;
  dimension->root = NULL;
  dimension->tree = tree;
  
  return tree;
}

Dimension *
SetDimensionName
( Dimension * dimension, const char * name )
{
  return NULL;
}

Tree *
SetDimensionOptions
( Dimension * dimension, Dictionary * options )
{
  return NULL;
}

Tree *
SetTreeDimension
( Tree * tree, Dimension * dimension )
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
DestroyNode
( Node * node, intptr_t previous )
{
  return;
}
