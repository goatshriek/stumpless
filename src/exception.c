#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/exception/initializer.h"
#include "private/type.h"
#include "private/utility/string.h"

static Dictionary *exception_dictionary = NULL;

Exception *
AddException
( Exception *e )
{
  void *value;

  if( !e || !e->name )
    return NULL;

  if( !exception_dictionary ){
    exception_dictionary = NewDictionary();

    if( !exception_dictionary )
      return NULL;
  }

  value = ( void * ) e;
  if( !SetDictionaryValue( exception_dictionary, e->name, value ) )
    return NULL;

  return e;
}

void
DestroyException
( Exception *e )
{
  if( e ){
    RemoveDictionaryValue( exception_dictionary, e->name );
    free( e );
  }

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
FindExceptionByName
( const char *name )
{
  Exception *e;

  if( !exception_dictionary ){
    exception_dictionary = NewDictionary();
    if( !exception_dictionary )
      return NULL;
  }

  e = GetDictionaryValue( exception_dictionary, name );

  if( !e )
    e = InitializeExceptionByName( name );

  return e;
}
