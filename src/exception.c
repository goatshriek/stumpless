#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/type.h>

#include "private/utility/string.h"

void
CatchException
( Exception *e )
{
  return;
}

char *
ExceptionToString
( Exception *e )
{
  if( !e )
    return NULL;
  else
    return copy_string( e->name );
}

Exception *
GetNextException
( void )
{
  return NULL;
}
