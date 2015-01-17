#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/comparator/base.h"
#include "private/container/tree.h"
#include "private/type.h"
#include "static/container/tree.h"
#include "test/helper.h"


const char * test_add_comparator( void );
const char * test_add_value( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_merge( void );
const char * test_next( void );
const char * test_set_options( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( add_comparator )
  RUN_TEST( add_value )
  RUN_TEST( begin )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( is_empty )
  RUN_TEST( merge )
  RUN_TEST( next )
  RUN_TEST( set_options )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_comparator
( void )
{
  Tree *tree;

  tree = NewTree();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  FAIL_IF_NULL( AddComparatorToTree( tree, BuildComparator() ), "the tree comparison could not be set" )

  // todo add test to make sure comparison is actually set

  return NULL;
}

const char *
test_add_value
( void )
{
  char *next, *str;
  Tree *result, *tree;

  tree = NewTree();
  FAIL_IF_NULL( tree, "a new tree could not be built" );

  FAIL_IF_NULL( AddComparatorToTree( tree, BuildComparator() ), "the tree comparison could not be set" )

  str = "first";
  result = AddToTree( tree, ( void * ) str );
  FAIL_IF_NULL( result, "an addition to an empty tree was not successfull" )

  next = BeginTree( tree );
  FAIL_IF_NULL( next, "could not get the first tree member" )
  ASSERT_STRINGS_EQUAL( "first", next, "the only element retrieved was not correct" )

  FAIL_IF_NOT_NULL( NextInTree( tree ), "there were extra elements added" )

  str = "third";
  result = AddToTree( tree, ( void * ) str );
  FAIL_IF_NULL( result, "a second addition was not successfull" )

  next = BeginTree( tree );
  FAIL_IF_NULL( next, "could not get the first tree member" )
  ASSERT_STRINGS_EQUAL( "first", next, "the first element retrieved was not correct" )

  next = NextInTree( tree );
  FAIL_IF_NULL( next, "could not get the second tree member" );
  ASSERT_STRINGS_EQUAL( "third", next, "the second element retrieved was not correct" )

  FAIL_IF_NOT_NULL( NextInTree( tree ), "there were extra elements added" )

  str = "second";
  result = AddToTree( tree, ( void * ) str );
  FAIL_IF_NULL( result, "a third addition was not successfull" )

  next = BeginTree( tree );
  FAIL_IF_NULL( next, "could not get the first tree member" )
  ASSERT_STRINGS_EQUAL( "first", next, "the first element retrieved was not correct" )

  next = NextInTree( tree );
  FAIL_IF_NULL( next, "could not get the second tree member" )
  ASSERT_STRINGS_EQUAL( "second", next, "the second element retrieved was not correct" )

  next = NextInTree( tree );
  FAIL_IF_NULL( next, "could not get the third tree member" );
  ASSERT_STRINGS_EQUAL( "third", next, "the third element retrieved was not correct" )

  FAIL_IF_NOT_NULL( NextInTree( tree ), "there were extra elements added" )

  return NULL;
}

const char *
test_begin
( void )
{
  const char *value;
  Tree *tree;

  tree = NewTree();
  FAIL_IF_NULL( tree, "a new tree could not be built" );

  value = BeginTree( tree );
  FAIL_IF_NOT_NULL( value, "an empty tree returned a value first" )

  tree = BuildTreeOfStrings();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  value = BeginTree( tree );
  FAIL_IF_NULL( value, "a value was not returned from the tree" )
  ASSERT_STRINGS_EQUAL( "first", value, "the first element of the tree was not returned" )

  DestroyTree(  tree );

  return NULL;
}

const char *
test_constructor
( void )
{
  Tree *tree;

  tree = NewTree();

  FAIL_IF_NULL( tree, "the tree was not created" )

  return NULL;
}

const char *
test_contains
( void )
{
  Tree *tree;
  void *value;

  tree = BuildTreeOfStrings();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  value = BeginTree( tree );
  FAIL_IF_NULL( value, "could not get the first tree member" )

  if( !TreeContains( tree, value ) )
    return "the tree did not contain a value pulled from the beginning";

  value = NextInTree( tree );
  if( !TreeContains( tree, value ) )
    return "the tree did not contain a value pulled from the middle";

  value = "not in the tree";
  if( TreeContains( tree, value ) )
    return "the tree contained a value not held in it";

  AddToTree( tree, value );
  if( !TreeContains( tree, value ) )
    return "the tree did not contain a value added to it";

  return NULL;
}

const char *
test_copy
( void )
{
  Tree *copy, *tree;

  tree = BuildTreeOfStrings();
  if( !tree )
    return "could not build the test tree";

  copy = CopyTree( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";

  copy = CopyTree( tree );
  if( !copy )
    return "the copy was null for a non-null pointer";
  if( copy == tree )
    return "the copy was equal to the original tree";
  // todo add tests for member copying

  return NULL;
}

const char *
test_destructor( void )
{
  Tree *tree;

  tree = NewTree();

  if( !tree )
    return "the tree was not created";

  DestroyTree( tree );

  tree = BuildTreeOfStrings();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  DestroyTree( tree );

  return NULL;
}

const char *
test_is_empty( void )
{
  Tree *tree = NULL;

  if( !TreeIsEmpty( tree ) )
    return "a null tree pointer was deemed empty";

  tree = NewTree();
  if( !TreeIsEmpty( tree ) )
    return "a newly created tree pointer was not deemed empty";

  tree = BuildTreeOfStrings();
  if( !tree )
    return "could not build the test tree";
  if( TreeIsEmpty( tree ) )
    return "a full tree was deemed empty";

  // todo add tests for a full tree made empty

  return NULL;
}

const char *
test_merge
( void )
{
  const char *first, *last;
  Tree *result, *tree_1, *tree_2;

  tree_1 = BuildTreeOfStrings();
  FAIL_IF_NULL( tree_1, "could not build the first tree" )

  tree_2 = BuildTreeOfStrings();
  FAIL_IF_NULL( tree_2, "could not build the second tree" )

  first = "AAA: this should be first";
  result = AddToTree( tree_2, ( void * ) first );
  FAIL_IF_NULL( result, "an extra value could not be added to the second tree" )

  last = "ZZZ: this should be last";
  result = AddToTree( tree_1, ( void * ) last );
  FAIL_IF_NULL( result, "an extra value could not be added to the first tree" )

  result = MergeTrees( NULL, NULL );
  FAIL_IF_NOT_NULL( result, "empty arguments did not cause an error" )

  result = MergeTrees( NULL, tree_2 );
  FAIL_IF_NOT_NULL( result, "an empty first argument did not cause an error" )

  result = MergeTrees( tree_1, NULL );
  FAIL_IF_NULL( result, "the tree was not successfully merged with nothing" )

  result = MergeTrees( tree_1, tree_2 );
  FAIL_IF_NULL( result, "the tree was not successfully appended" )
  if( BeginTree( tree_1 ) != first )
    return "the trees were not properly merged";

  return NULL;
}

const char *
test_next
( void )
{
  const char *value;
  Tree *tree;

  tree = BuildTreeOfStrings();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  value = BeginTree( tree );
  FAIL_IF_NULL( value, "a value was not returned from the begin call" )
  ASSERT_STRINGS_EQUAL( "first", value, "the first value in the tree was not returned by the begin call" )

  value = NextInTree( tree );
  FAIL_IF_NULL( value, "a second value was not returned" )
  ASSERT_STRINGS_EQUAL( "second", value, "the second value in the tree was not returned" )

  value = NextInTree( tree );
  FAIL_IF_NULL( value, "a third value was not returned" )
  ASSERT_STRINGS_EQUAL( "third", value, "the third value in the tree was not returned" )

  value = NextInTree( tree );
  FAIL_IF_NOT_NULL( value, "a value beyond the last was returned" )

  return NULL;
}

const char *
test_set_options
( void )
{
  Dictionary *options;
  Tree *tree;

  tree = NewTree();
  FAIL_IF_NULL( tree, "could not build the test tree" )

  FAIL_IF_NOT_NULL( tree->options, "a new tree had options" )

  options = BuildDictionaryOfStrings();
  FAIL_IF_NULL( options, "could not build the test dictionary" )

  FAIL_IF_NULL( SetTreeOptions( tree, options ), "could not set the options of a tree" )
  if( tree->options != options )
    return "the options of the tree were not actually set";

  return NULL;
}
