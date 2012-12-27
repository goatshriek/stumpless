#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

void
print_array ( unsigned * array, unsigned size )
{
  printf ( "[" );
  
  for ( unsigned i = 0; i < size; i++ ) {
    printf ( "%11d", array[i] );
    if ( i+1 < size )
      printf ( ", " );
  }
  
  printf ( "]\n" );
}

void
quicksort ( unsigned * array, unsigned size )
{
  return;
}

/*
 * Quicksorts a random array, printing the array at each iteration step
 */
int
main ( void )
{
  // seed the random number generator
  srand ( (unsigned)time ( NULL ) );
  
  // initialize the array values
  unsigned array[ARRAY_SIZE];
  for ( unsigned i = 0; i < ARRAY_SIZE; i++ )
    array[i] = ( rand () - RAND_MAX / 2 ) % 10;
  
  print_array ( array, ARRAY_SIZE );

  quicksort ( array, ARRAY_SIZE );
  
  return EXIT_SUCCESS;
}
