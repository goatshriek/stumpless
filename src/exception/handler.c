#include <stumpless/exception/handler.h>
#include <stumpless/type.h>

static exception_handler_function_t memory_allocation_handler;

exception_handler_function_t
GetMemoryAllocationExceptionHandler
( void )
{
  return memory_allocation_handler;
}

void
SetMemoryAllocationExceptionHandler
( void (*handler)( const Exception *) )
{
  memory_allocation_handler = handler;
  return;
}
