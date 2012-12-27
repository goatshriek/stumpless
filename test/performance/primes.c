#include <stdio.h>
#include <stdlib.h>

#define NUM_PRIMES 10000

/*
 * Prints out the first NUM_PRIME prime numbers.
 */
int
main ( void )
{
  unsigned primes[NUM_PRIMES];
  unsigned prime_count = 0, divisible, i, j;
  
  for ( i = 2; prime_count < NUM_PRIMES; i++ ) {
    divisible = 0;
    
    if ( divisible )
      continue;
    
    for ( j = 0; !divisible && j < prime_count && primes[j] < ( i/2 + 1 ); j++ )
      divisible |= ( i % primes[j] == 0 );
    
    if ( !divisible ) {
      primes[prime_count++] = i;
      printf ( "%d\n", i );
    }
      
  }
  
  return EXIT_SUCCESS;
}
