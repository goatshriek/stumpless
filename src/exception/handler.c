#include <stdlib.h>

#include <stumpless/exception/handler.h>
#include <stumpless/type.h>

static exception_handler_function_t memory_allocation_handler = NULL;

exception_handler_function_t
GetMemoryAllocationExceptionHandler
( void )
{
  return memory_allocation_handler;
}

void
SetMemoryAllocationExceptionHandler
( exception_handler_function_t handler )
{
  memory_allocation_handler = handler;
}
