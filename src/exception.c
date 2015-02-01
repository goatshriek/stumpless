#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/type.h>

#include "private/exception/thrower.h"
#include "private/utility/string.h"

void
CatchException
( Exception *e )
{
  DestroyException( e );
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
GetUncaughtException
( void )
{
  return GetNextException();
}
