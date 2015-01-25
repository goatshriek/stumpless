#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/exception/initializer.h"
#include "private/type.h"

#define ADD_STATUS( name, function )                                           \
SetDictionaryValue( initializers, name, Initialize##function##Exception );

#define CREATE_EXCEPTION                                                       \
Exception *e = malloc( sizeof( Exception ) );                                  \
if( !e )                                                                       \
  return NULL;

static Dictionary *initializers = NULL;

Exception *
InitializeConstructorFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "constructor failure";
  e->message = "a call to a constructor has failed, perhaps resulting from a memory allocation failure or invalid argument";
  e->failure = 1;
  e->informational = 0;
  e->warning = 0;

  return e;
}

Exception *
InitializeDictionaryFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "dictionary failure";
  e->message = "an operation on an underlying dictionary structure has failedfrom either a memory allocation failure or a malformed dictionary state";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeDuplicateException
( void )
{
  CREATE_EXCEPTION

  e->name = "duplicate";
  e->message = "an attempt to add to a collection detected the same member already existing in the collection";
  e->informational = 1;
  e->failure = 0;
  e->warning = 0;

  return e;
}

Exception *
InitializeEmptyArgumentException
( void )
{
  CREATE_EXCEPTION

  e->name = "empty argument";
  e->message = "an argument required for the operation was either NULL or an empty structure";
  e->informational = 1;
  e->failure = 0;
  e->warning = 0;

  return e;
}

Exception *
InitializeEventFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "event failure";
  e->message = "an Event could not be found";
  e->informational = 1;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeForkFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "fork failure";
  e->message = "a call to fork failed";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeIncompatibleProfileException
( void )
{
  CREATE_EXCEPTION

  e->name = "incompatible profile";
  e->message = "the profile of an object used for the request operation did not support the operation in question";
  e->informational = 1;
  e->failure = 0;
  e->warning = 0;

  return e;
}

Exception *
InitializeListFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "list failure";
  e->message = "an operation on an underlying list structure has failed due to either a memory allocation failure or a malformed list structure";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeMalformedStructureException
( void )
{
  CREATE_EXCEPTION

  e->name = "malformed structure";
  e->message = "one of the internal structures is not properly formed, for example a length higher than an array size";
  e->informational = 1;
  e->failure = 0;
  e->warning = 0;

  return e;
}

Exception *
InitializePipeFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "pipe failure";
  e->message = "a call to pipe failed";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeExceptionByName
( const char * name )
{
  Exception *( *initializer )();

  if( !initializers ){

    initializers = NewDictionary();
    if( !initializers )
      return NULL;

    ADD_STATUS( "constructor failure", ConstructorFailure )
    ADD_STATUS( "dictionary failure", DictionaryFailure )
    ADD_STATUS( "duplicate", Duplicate )
    ADD_STATUS( "empty argument", EmptyArgument )
    ADD_STATUS( "fork failure", ForkFailure )
    ADD_STATUS( "incompatible profile", IncompatibleProfile )
    ADD_STATUS( "list failure", ListFailure )
    ADD_STATUS( "malformed structure", MalformedStructure )
    ADD_STATUS( "pipe failure", PipeFailure )
    ADD_STATUS( "stream write failure", StreamWriteFailure )
    ADD_STATUS( "string write failure", StringWriteFailure )
    ADD_STATUS( "value profile not found", ValueProfileNotFound )
  }

  initializer = GetDictionaryValue( initializers, name );

  if( !initializer )
    return NULL;
  else
    return AddException( initializer() );
}

Exception *
InitializeStreamWriteFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "stream write failure";
  e->message = "an attempt to write to a stream failed, error indicators may give more information";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeStringWriteFailureException
( void )
{
  CREATE_EXCEPTION

  e->name = "string write failure";
  e->message = "an attempt to write to a string failed, perhaps because the string was not large enough";
  e->informational = 0;
  e->failure = 1;
  e->warning = 0;

  return e;
}

Exception *
InitializeValueProfileNotFoundException
( void )
{
  CREATE_EXCEPTION

  e->name = "value profile not found";
  e->message = "the value profile specified could not be found in the running list or in the default list, perhaps due to a misspelling";
  e->informational = 1;
  e->failure = 0;
  e->warning = 0;

  return e;
}
