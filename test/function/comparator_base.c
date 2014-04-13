#include <stdio.h>
#include <stdlib.h>

#include "private/comparator_base.h"
#include "private/dictionary.h"
#include "private/type.h"

#include "helper.h"

const char * test_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_string
( void )
{
  void * str_0 = ( void * ) "first";
  void * str_1 = ( void * ) "first";
  void * str_2 = ( void * ) "second";
  void * str_3 = ( void * ) "third";
  void * str_4 = ( void * ) "thirdly";
  Dictionary * options = NewDictionary();
  
  if( StringComparatorCompare( str_0, str_0, options ) != 0 )
    return "the same value was not equal";
  
  if( StringComparatorCompare( str_0, str_1, options ) != 0 )
    return "two equal strings were not equal";
  
  if( StringComparatorCompare( str_1, str_2, options ) >= 0 )
    return "first did not come before second";
  
  if( StringComparatorCompare( str_2, str_1, options ) <= 0 )
    return "second did not come after first";
  
  if( StringComparatorCompare( str_3, str_4, options ) >= 0 )
    return "a shorter string did not come before a longer one";
  
  return NULL;
}
