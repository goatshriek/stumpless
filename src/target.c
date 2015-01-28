#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/target.h>

#include "private/formatter.h"
#include "private/handler.h"
#include "private/type.h"

Target *
CopyTarget
( const Target *target )
{
  Target *copy;

  if( !target )
    return NULL;

  copy = malloc( sizeof( Target ) );
  if( !copy )
    return NULL;

  memcpy( copy, target, sizeof( Target ) );

  return copy;
}

void
DestroyTarget
( Target *target )
{
  if( !target )
    return;

  free( target );

  return;
}

Exception *
LogToTarget
( Target *target, const Record *record )
{
  if( !target || !target->formatter || !target->handler || !record )
    return NULL;

  HandleOutput( target->handler, FormatRecord( target->formatter, record ) );
  return NULL;
}
