#include <stdlib.h>
#include <string.h>

#include <string_helper.h>

// returns 0 if the string contains anything other than whitespace
// otherwise returns a non-zero value (the length of the string, or
// 1 for a NULL pointer)
unsigned short
is_empty( const char * str )
{
  if( str == NULL )
    return 1;
  
  unsigned index = 0;
  char next = str[0];
  
  while( str[index] != '\0' ){
    if( !isspace( str[index] ) )
      return 0;
    
    index++;
  }
  
  return index;
}
