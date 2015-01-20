#include <stdlib.h>

#include <stumpless/type.h>

#include "private/exception/thrower.h"

Exception *
ThrowMemoryAllocationException
( void )
{
  Exception *e;

  e = malloc( sizeof( Exception ) );
  if( !e )
    return NULL;

  e->name = "memory allocation failure";
  e->message = "a request for allocated memory was denied, likely meaning that there is none left";

  return e;
}
