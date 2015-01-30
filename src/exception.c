#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/type.h"
#include "private/utility/string.h"

void
DestroyException
( Exception *e )
{
  free( e );

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
