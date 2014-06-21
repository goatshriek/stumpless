#include <stdio.h>
#include <stdlib.h>

#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/handler/stream.h"
#include "private/status.h"
#include "private/type.h"

Status *
BinaryOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
CSVOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
HandleStreamOutput
( const Output * output, Dictionary * options )
{
  if( !output )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !output->profile || !output->profile->into_stream )
    return RaiseAbnormalStatus( "incompatible profile" );
  
  FILE * destination = stdout;
  
  return output->profile->into_stream( output, destination );
}

Status *
JSONOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
RawStringOutputIntoStream
( const Output * output, FILE * stream )
{
  if( !output || !stream )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !output->data || !output->data->c_p )
    return RaiseAbnormalStatus( "malformed structure" );
  
  if( fputs( output->data->c_p, stream ) < 0 )
    return RaiseAbnormalStatus( "stream write failure" );
  
  return NULL;
}

Status *
TextOutputIntoStream
( const Output * output, FILE * stream )
{
  if( !output || !stream )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !output->data || !output->data->v_p )
    return RaiseAbnormalStatus( "malformed structure" );
  
  const Value * value;
  ValueListConstIterator * values = CBeginValueList( output->data->v_p );
  while( value = NextInValueListConstIterator( values ) ){
    if( !value->data ){
      DestroyValueListConstIterator( values );
      return RaiseAbnormalStatus( "malformed structure" );
    }
  
    if( fputs( value->data->c_p, stream ) < 0 ){
      DestroyValueListConstIterator( values );
      return RaiseAbnormalStatus( "stream write failure" );
    }
  }
  
  DestroyValueListConstIterator( values );
  
  return NULL;
}

Status *
XMLOutputIntoStream
( const Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}
