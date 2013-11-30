#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/tree.h"
#include "private/stack.h"
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
  
  // todo finish
  
  return dimension;
}

Tree *
AddToTree
( Tree * tree, void * value )
{
  Node * node = NewNode( 10 );
  if( node == NULL )
    return NULL;
  
  node->value = value;
  
  Dimension * dimension = BeginList( tree->dimensions );
  while( dimension != NULL ){
    if( AddToDimension( dimension, node ) == NULL )
      return NULL;
    
    dimension = NextInList( tree->dimensions );
  }
  
  return tree;
}

Tree *
AddListToTree
( Tree * tree, List * list )
{
  if( tree == NULL || list == NULL )
    return NULL;
  
  void * value = BeginList( value );
  while( value != NULL ){
    AddToTree( tree, value );
    
    value = NextInList( value );
  }
  
  return tree;
}

void *
BeginDimension
( Dimension * dimension )
{
  Iterator * iterator = NewIterator( dimension );
  if( dimension->iterator == NULL )
    return NULL;
  
  dimension->iterator = iterator;
  
  return NextInIterator( iterator );
}

void *
BeginTree
( Tree * tree )
{
  if( tree == NULL )
    return NULL;
  else
    return BeginDimension( tree->current_dimension );
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
  
  // todo remove dimension from tree's list
  
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
  if( dimension == NULL )
    return NULL;
  else
    return NextInIterator( dimension->iterator );
}

void *
NextInTree
( Tree * tree )
{
  if( tree == NULL )
    return NULL;
  else
    return NextInDimension( tree->current_dimension );
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
  
  if( AppendToList( tree->dimensions, dimension ) == NULL )
    return NULL;
  
  tree->current_dimension = dimension;
  tree->dimension_capacity = 20;
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
      || tree->current_dimension == NULL
      || tree->current_dimension->root == NULL;
}

// todo refactor this beast of a function
static
Dimension *
AddToDimension
( Dimension * dimension, Node * node )
{
  Stack * path = NewStack();
  if( path == NULL )
    return NULL;
  
  short result;
  unsigned index = dimension->index;
  Dictionary * options = dimension->options;
  Node * current = dimension->root;
  
  if( current == NULL ){
    dimension->root = node;
    return dimension;
  }
  
  while( current != NULL ){
    PushToStack( path, current );
    result = RunComparisonList( dimension->comparisons, node->value, current->value, options );
    if( result == 0 ){
      DestroyStack( path );
      return dimension;
    }
    
    if( result < 0 ){
      if( current->left_children[index] == NULL ){
        current->left_children[index] = node;
        
        if( current->right_children[index] == NULL ){
          PushToStack( path, node );
          RestructureDimension( dimension, path );
        } else {
          node->heights[index] = 1;
        }
        
        DestroyStack( path );
        return dimension;
      } else {
        current = current->left_children[index];
      }
    } else {
      if( current->right_children[index] == NULL ){
        current->right_children[index] = node;
      
        if( current->left_children[index] == NULL ){
          PushToStack( path, node );
          RestructureDimension( dimension, path );
        } else {
          node->heights[index] = 1;
        }
      
        DestroyStack( path );
        return dimension;
      } else {
        current = current->right_children[index];
      }
    }
  }
  
  return NULL;
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
  
  free( node->heights );
  free( node->left_children );
  free( node->right_children );
  free( node );
  
  DestroyNode( left );
  DestroyNode( right );
  
  return;
}

static
unsigned short
IteratorIsDone
( Iterator * iterator)
{
  return iterator == NULL || StackIsEmpty( iterator->path );
}

static
unsigned
MaxNodeHeight
( Node * first, Node * second, unsigned index )
{
  unsigned first_height, second_height;
  
  if( first == NULL )
    first_height = 0;
  else
    first_height = first->heights[index];
  
  if( second == NULL )
    second_height = 0;
  else
    second_height = second->heights[index];
  
  if( first_height > second_height )
    return first_height;
  else
    return second_height;
}

static
Iterator *
NewIterator
( Dimension * dimension )
{
  if( dimension == NULL )
    return NULL;
  
  Iterator * iterator = malloc( sizeof( Iterator ) );
  if( iterator == NULL )
    return NULL;
  
  iterator->path = NewStack();
  if( iterator->path == NULL )
    return NULL;
  
  iterator->index = dimension->index;
  
  Stack * result;
  Node * current = dimension->root;
  while( current != NULL ){
    result = PushToStack( iterator->path, current );
    if( result == NULL )
      return NULL;
    
    current = current->left_children[iterator->index];
  }
  
  return iterator;
}

static
Node *
NewNode
( unsigned dimension_capacity )
{
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return NULL;
  
  node->left_children = malloc( sizeof( Node * ) * dimension_capacity );
  if( node->left_children == NULL )
    return NULL;
  
  node->right_children = malloc( sizeof( Node * ) * dimension_capacity );
  if( node->right_children == NULL )
    return NULL;
  
  node->heights = malloc( sizeof( unsigned ) * dimension_capacity );
  if( node->heights == NULL )
    return NULL;
  
  unsigned i;
  for( i = 0; i < dimension_capacity; i++ ){
    node->left_children[i] = NULL;
    node->right_children[i] = NULL;
    node->heights[i] = 0;
  }
  
  node->value = NULL;
   
  return node;
}


// todo refactor
static
void *
NextInIterator
( Iterator * iterator )
{
  if( iterator == NULL )
    return NULL;
  
  unsigned index = iterator->index;
  Node * current = PopFromStack( iterator->path );
  void * value = current->value;
  Stack * result;
  
  if( current->right_children[index] == NULL ){
    current = PopFromStack( iterator->path );
    
    while( current != NULL && current->right_children[index] == NULL ){
      current = PopFromStack( iterator->path );
    }
    
    if( current == NULL )
      return NULL;
    
    current = current->right_children[index];
    result = PushToStack( iterator->path, current );
    if( result == NULL )
      return NULL;
    
    while( current->left_children[index] != NULL ){
      result = PushToStack( iterator->path, current->left_children[index] );
      if( result == NULL )
        return NULL;
      
      current = current->left_children[index];
    }
  } else {
    result = PushToStack( iterator->path, current->right_children[index] );
    if( result == NULL )
      return NULL;
    
    current = current->right_children[index];
    while( current->left_children[index] != NULL ){
      result = PushToStack( iterator->path, current->left_children[index] );
      if( result != NULL )
        return NULL;
      
      current = current->left_children[index];
    }
  }
  
  return value;
}

// todo refactor this monstrous function
static
Dimension *
RestructureDimension
( Dimension * dimension, Stack * stack )
{
  unsigned index = dimension->index;
  
  unsigned left_height, right_height;
  int difference;
  Stack * changed = NewStack();
  if( changed == NULL )
    return NULL;
  
  Node * current = PopFromStack( stack );
  while( current != NULL ){
    PushToStack( changed, current );
    current->heights[index]++;
    
    if( current->left_children[index] == NULL )
      left_height = 0;
    else
      left_height = current->left_children[index]->heights[index];
    
    if( current->right_children[index] == NULL )
      right_height = 0;
    else
      right_height = current->right_children[index]->heights[index];
    
    difference = left_height - right_height;
    
    if( difference > 1 || difference < -1 )
      break;
    else
      current = PopFromStack( stack );
  }
  
  if( current == NULL )
    return dimension;
  
  Node * grandparent = PopFromStack( changed );
  Node * parent = PopFromStack( changed );
  Node * bottom = PopFromStack( changed );
  DestroyStack( changed );
  
  Node * first, * middle, * last;
  Node * tree_1, * tree_2, * tree_3, * tree_4;
  
  if( grandparent->left_children[index] != parent ){
    first = grandparent;
    tree_1 = grandparent->left_children[index];
    if( parent->left_children[index] != bottom ){
      middle = parent;
      last = bottom;
      
      tree_2 = parent->left_children[index];
      tree_3 = bottom->left_children[index];
      tree_4 = bottom->right_children[index];
    } else {
      last = parent;
      middle = bottom;
      
      tree_2 = bottom->left_children[index];
      tree_3 = bottom->right_children[index];
      tree_4 = parent->right_children[index];
    }
  } else {
    last = grandparent;
    tree_4 = grandparent->right_children[index];
    if( parent->left_children[index] != bottom ){
      first = parent;
      middle = bottom;
      
      tree_1 = parent->left_children[index];
      tree_2 = bottom->left_children[index];
      tree_3 = bottom->right_children[index];
    } else {
      middle = parent;
      first = bottom;
      
      tree_1 = bottom->left_children[index];
      tree_2 = bottom->right_children[index];
      tree_3 = parent->right_children[index];
    }
  }
  
  Node * great_grandparent = PeekAtStack( stack );
  if( great_grandparent == NULL )
    dimension->root = middle;
  else if( great_grandparent->left_children[index] == grandparent )
    great_grandparent->left_children[index] = middle;
  else
    great_grandparent->right_children[index] = middle;
  
  middle->left_children[index] = first;
  middle->right_children[index] = last;
  
  first->left_children[index] = tree_1;
  first->right_children[index] = tree_2;
  
  last->left_children[index] = tree_3;
  last->right_children[index] = tree_4;
  
  first->heights[index] = MaxNodeHeight( tree_1, tree_2, index ) + 1;
  last->heights[index] = MaxNodeHeight( tree_3, tree_4, index ) + 1;
  middle->heights[index] = MaxNodeHeight( first, last, index ) + 1;
  
  current = PopFromStack( stack );
  while( current != NULL ){
    current->heights[index] = MaxNodeHeight( current->left_children[index], current->right_children[index], index ) + 1;
    current = PopFromStack( stack );
  }
  
  return dimension;
}

static
short
RunComparisonList
( List * list, void * value_1, void * value_2, Dictionary * options )
{
  if( list == NULL )
    return 0;
  
  short result;
  comparison_t comparison = BeginList( list );
  while( comparison != NULL ){
    result = comparison( value_1, value_2, options );
    if( result != 0 )
      return result;
    
    comparison = NextInList( list );
  }
  
  return 0;
}
