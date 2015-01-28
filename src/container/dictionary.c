#include <stdlib.h>
#include <string.h>

#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "static/container/dictionary.h"

DictionaryConstIterator *
CBeginDictionary
( const Dictionary *dictionary )
{
  return NewDictionaryConstIterator( dictionary, 0 );
}

void
DestroyDictionary
( Dictionary *dictionary )
{
  if( !dictionary )
    return;

  DestroyNode( dictionary->root );

  free( dictionary );
}

unsigned short
DictionaryIsEmpty
( const Dictionary *dictionary )
{
  return dictionary == NULL || dictionary->root == NULL;
}

void *
GetDictionaryValue
( Dictionary *dictionary, const char *key )
{
  Node *result;

  if( !dictionary || !key )
    return NULL;

  result = GetNode( key, dictionary->root );

  if( !result )
    return NULL;

  Splay( dictionary, result );
  return result->value;
}

// todo implement
Dictionary *
MergeDictionaries
( Dictionary *primary, Dictionary *secondary )
{
  return NULL;
}

Dictionary *
NewDictionary
()
{
  Dictionary * dictionary = malloc( sizeof( Dictionary ) );
  if( !dictionary )
    return NULL;

  dictionary->root = NULL;

  return dictionary;
}

void *
RemoveDictionaryValue
( Dictionary *dictionary, const char *key )
{
  Node *minimum, *node;
  void *removed_value;

  node = GetNode( key, dictionary->root );
  if( !node )
    return NULL;

  Splay( dictionary, node );

  if( !node->left_child ){
    ReplaceNode( dictionary, node, node->right_child );
  } else if( !node->right_child ){
    ReplaceNode( dictionary, node, node->left_child );
  } else {
    minimum = SubtreeMinimum( node->right_child );
    if( minimum->parent != node ){
      ReplaceNode( dictionary, minimum, minimum->right_child );
      minimum->right_child = node->right_child;
      minimum->right_child->parent = minimum;
    }
    ReplaceNode( dictionary, node, minimum );
    minimum->left_child = node->left_child;
    minimum->left_child->parent = minimum;
  }

  removed_value = node->value;
  node->left_child = NULL;
  node->right_child = NULL;
  DestroyNode( node );
  return removed_value;
}

Dictionary *
SetDictionaryValue
( Dictionary *dictionary, const char *key, void *value )
{
  Node *node;

  // todo add a search for existing keys
  if( !dictionary || !key )
    return NULL;

  if( !value ){
    RemoveDictionaryValue( dictionary, key );
    return NULL;
  }

  node = malloc( sizeof( Node ) );
  if( !node )
    return NULL;

  node->key = key;
  node->value = value;
  node->parent = NULL;
  node->left_child = NULL;
  node->right_child = NULL;

  if( !dictionary->root ){
    dictionary->root = node;
    return dictionary;
  }

  AddNode( dictionary->root, node );
  Splay( dictionary, node );

  return dictionary;
}

static
void
AddNode
( Node *node, Node *addition )
{
  int comparison;
  Node *next;

  comparison =  strcmp( addition->key, node->key );

  if( comparison == 0 ){
    node->value = addition->value;
    // todo deal with memory leak introduced by not freeing the node
    return;
  }

  if( comparison < 0 ){
    next = node->left_child;
    if( !next ){
      node->left_child = addition;
      addition->parent = node;
      return;
    }
  } else {
    next = node->right_child;
    if( !next ){
      node->right_child = addition;
      addition->parent = node;
      return;
    }
  }

  AddNode( next, addition );

  return;
}

static
void
DestroyNode
( Node *node )
{
  if( !node )
    return;

  DestroyNode( node->left_child );
  DestroyNode( node->right_child );

  free( node );
}

static
Node *
GetNode
( const char *key, Node *node )
{
  int comparison;
  Node *next;

  if( !node || !node->key )
    return NULL;

  comparison =  strcmp( key, node->key );
  if( comparison == 0 )
    return node;

  if( comparison < 0 )
    next = node->left_child;
  else
    next = node->right_child;

  return GetNode( key, next );
}

static
void
LeftRotate
( Dictionary *dictionary, Node *node )
{
  Node *old_right;

  old_right = node->right_child;
  node->right_child = old_right->left_child;

  if( old_right->left_child )
    old_right->left_child->parent = node;

  old_right->parent = node->parent;

  if( !node->parent )
    dictionary->root = old_right;
  else if( node == node->parent->left_child )
    node->parent->left_child = old_right;
  else
    node->parent->right_child = old_right;

  old_right->left_child = node;
  node->parent = old_right;
}

static
void
ReplaceNode
( Dictionary *dictionary, Node *previous, Node *replacement )
{
  if( !previous->parent )
    dictionary->root = replacement;
  else if( previous == previous->parent->left_child )
    previous->parent->left_child = replacement;
  else
    previous->parent->right_child = replacement;

  if( replacement )
    replacement->parent = previous->parent;
}
static
void
RightRotate
( Dictionary *dictionary, Node *node )
{
  Node *old_left;

  old_left = node->left_child;
  node->left_child = old_left->right_child;

  if( old_left->right_child )
    old_left->right_child->parent = node;

  old_left->parent = node->parent;

  if( !node->parent )
    dictionary->root = old_left;
  else if( node == node->parent->left_child )
    node->parent->left_child = old_left;
  else
    node->parent->right_child = old_left;

  old_left->right_child = node;
  node->parent = old_left;
}

static
void
Splay
( Dictionary *dictionary, Node *node )
{
  if( !node->parent )
    return;

  if( !node->parent->parent ){
    if( node->parent->left_child == node )
      RightRotate( dictionary, node->parent );
    else
      LeftRotate( dictionary, node->parent );
  } else if( node->parent->left_child == node
             && node->parent->parent->left_child == node->parent ){
    RightRotate( dictionary, node->parent->parent );
    RightRotate( dictionary, node->parent );
  } else if( node->parent->right_child == node
             && node->parent->parent->right_child == node->parent ){
    LeftRotate( dictionary, node->parent->parent );
    LeftRotate( dictionary, node->parent );
  } else if( node->parent->left_child == node
             && node->parent->parent->right_child == node->parent ){
    RightRotate( dictionary, node->parent );
    LeftRotate( dictionary, node->parent );
  } else {
    LeftRotate( dictionary, node->parent );
    RightRotate( dictionary, node->parent );
  }

  Splay( dictionary, node );
}

static
Node *
SubtreeMinimum
( Node *node )
{
  if( !node->left_child )
    return node;

  return SubtreeMinimum( node->left_child );
}
