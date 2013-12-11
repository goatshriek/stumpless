#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/tree.h"
#include "private/static/tree.h"
#include "private/type.h"

Dimension *
AddComparisonToDimension
( Dimension * dimension, comparison_t comparison )
{
  if( dimension == NULL )
    return NULL;
  
  if( dimension->comparisons == NULL ){
    dimension->comparisons = NewList();
    if( dimension->comparisons == NULL )
      return NULL;
  }
  
  if( AppendToList( dimension->comparisons, comparison ) == NULL )
    return NULL;
  
  return dimension;
}

Tree *
AddComparisonToTree
( Tree * tree, comparison_t comparison )
{
  if( tree == NULL )
    return NULL;
  
  if( AddComparisonToDimension( tree->current_dimension, comparison ) == NULL )
    return NULL;
  
  return tree;
}

Dimension *
AddDimensionToTree
( Tree * tree, const char * name )
{
  Dimension * dimension = malloc( sizeof( Dimension ) );
  if( dimension == NULL )
    return NULL;
  
  dimension->comparisons = NULL;
  dimension->name = name;
  dimension->tree = tree;
  
  // todo finish function
  
  return dimension;
}

Tree *
AddToTree
( Tree * tree, void * value )
{
  // todo finish
  
  return NULL;
}

Tree *
AddListToTree
( Tree * tree, List * list )
{
  // todo finish
  
  return NULL;
}

void *
BeginDimension
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

void *
BeginTree
( Tree * tree )
{
  // todo finish
  
  return NULL;
}

Tree *
CopyTree
( Tree * tree )
{
  // todo finish
  
  return NULL;
}

void
DestroyDimension
( Dimension * dimension )
{
  if( dimension == NULL )
    return;
  
  DestroyList( dimension->comparisons );
  
  free( dimension );
  
  return;
}

void
DestroyTree
( Tree * tree )
{
  if( tree == NULL )
    return;
  
  Dimension * dimension = BeginList( tree->dimensions );

  if( dimension != NULL )
    DestroyNode( dimension->root );
  
  while( dimension != NULL ){
    DestroyDimension( dimension );
    dimension = NextInList( tree->dimensions );
  }
  
  DestroyList( tree->dimensions );
  
  return;
}

Tree *
MergeTrees
( Tree * tree_1, Tree * tree_2 )
{
  // todo finish
  
  return NULL;
}

void *
NextInDimension
( Dimension * dimension )
{
  // todo finish
  
  return NULL;
}

void *
NextInTree
( Tree * tree )
{
  // todo finish
  
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
  
  tree->current_dimension = dimension;
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
  if( dimension == NULL )
    return NULL;
  
  dimension->name = name;
  
  return dimension;
}

Dimension *
SetDimensionOptions
( Dimension * dimension, Dictionary * options )
{
  if( dimension == NULL )
    return NULL;
  
  dimension->options = options;
  
  return dimension;
}

Tree *
SetTreeDimension
( Tree * tree, Dimension * dimension )
{
  if( tree == NULL )
    return NULL;
  
  tree->current_dimension = dimension;
  
  return tree;
}

Tree *
SetTreeOptions
( Tree * tree, Dictionary * options )
{
  if( tree == NULL )
    return NULL;
  
  tree->options = options;
  
  return tree;
}

unsigned short
TreeContains
( Tree * tree, void * value )
{
  // todo finish
  return 0;
}

unsigned short
TreeIsEmpty
( Tree * tree )
{
  return tree == NULL
      || BeginDimension( BeginList( tree->dimensions ) ) == NULL;
}

static
void
DestroyNode
( Node * node )
{
  if( node == NULL )
    return;
  
  Node * left = node->left_children[0];
  Node * right = node->right_children[0];
  
  free( node->left_children );
  free( node->right_children );
  free( node );
  
  DestroyNode( left );
  DestroyNode( right );
  
  return;
}
