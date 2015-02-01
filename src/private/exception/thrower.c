#include <stdlib.h>

#include <stumpless/exception/handler.h>

#include "private/container/queue.h"
#include "private/exception/thrower.h"
#include "private/type.h"

static Queue *exceptions = NULL;

void
DestroyException
( Exception *e )
{
  RemoveFromQueue( exceptions, e );
  free( e );
}

Exception *
GetNextException
( void )
{
  return PeekAtQueue( exceptions );
}

Exception *
ThrowMemoryAllocationException
( void )
{
  Exception *e;
  exception_handler_function_t handler;

  e = malloc( sizeof( Exception ) );
  if( !e )
    return NULL;

  e->name = "memory allocation failure";
  e->message = "a request for allocated memory was denied, likely meaning that there is none left";

  if( !exceptions )
    exceptions = NewQueue();
  PushToQueue( exceptions, e );

  handler = GetMemoryAllocationExceptionHandler();
  if( handler )
    handler( e );

  return e;
}
