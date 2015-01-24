#include <stdlib.h>

#include <stumpless/exception/handler.h>
#include <stumpless/type.h>

#include "private/exception/thrower.h"

Exception *
ThrowMemoryAllocationException
( void )
{
  Exception *e;
  void (*handler)( const Exception *);

  e = malloc( sizeof( Exception ) );
  if( !e )
    return NULL;

  e->name = "memory allocation failure";
  e->message = "a request for allocated memory was denied, likely meaning that there is none left";

  handler = GetMemoryAllocationExceptionHandler();
  if( handler )
    handler( e );

  return e;
}
