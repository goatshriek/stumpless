#include "private/target.h"
#include "private/type.h"

Status *
LogToTarget
( const Target *target, Entry *entry )
{
  if( !target || !target->formatter || !target->handler || !entry )
    return RaiseStatus( "empty argument" );
  
  EntryThroughAdapterList( target->adapters, entry );
 
  HandleOutput( target->handler, FormatEntry( target->formatter, entry ) );
  
  return NULL;
}
