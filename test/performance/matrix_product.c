#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_DIMENSION 100

void
print_matrix ( unsigned matrix[MATRIX_DIMENSION][MATRIX_DIMENSION] )
{
  unsigned i, j;
  
  for ( i = 0; i < MATRIX_DIMENSION; i++ ) {
    printf ( "| " );
    
    for ( j = 0; j < MATRIX_DIMENSION; j++ )
      printf ( "%11d ", matrix[i][j] );
    
    printf ( " |\n" );
  }
  
  printf ( "\n" );
  return;
}

/*
 * Calculates the cross product of two matrices.
 */
int
main ( void )
{
  unsigned a[MATRIX_DIMENSION][MATRIX_DIMENSION];
  unsigned b[MATRIX_DIMENSION][MATRIX_DIMENSION];
  unsigned c[MATRIX_DIMENSION][MATRIX_DIMENSION];
  unsigned i, j, k;
  
  srand ( (unsigned) time ( NULL ) );
  
  for ( i = 0; i < MATRIX_DIMENSION; i++ ) {
    for ( j = 0; j < MATRIX_DIMENSION; j++ ) {
      a[i][j] = rand () - RAND_MAX / 2;
      b[i][j] = rand () - RAND_MAX / 2;
    }
  }
  
  print_matrix ( a );
  print_matrix ( b );
  
  for ( i = 0; i < MATRIX_DIMENSION; i++ ) {
    for ( j = 0; j < MATRIX_DIMENSION; j++ ) {
      c[i][j] = 0;
      
      for ( k = 0; k < MATRIX_DIMENSION; k++ ) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  
  print_matrix ( c );
  return EXIT_SUCCESS;
}
