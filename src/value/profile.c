#include <stdlib.h>

#include <stumpless/value/profile.h>

#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/type.h"
#include "private/value/profile_initializer.h"

static Dictionary *profiles = NULL;

Status *
AddValueProfile
( ValueProfile *profile )
{
  if( !profile || !profile->name )
    return NULL;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return RaiseStatus( "constructor failure" );
  }

  void *value = ( void * ) profile;
  if( !SetDictionaryValue( profiles, profile->name, value ) )
    return NULL;

  return NULL;
}

ValueProfile *
FindValueProfileByName
( const char *name )
{
  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return NULL;
  }

  ValueProfile *profile = GetDictionaryValue( profiles, name );

  if( !profile ){
    if( InitializeValueProfileByName( name ) )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }

  return profile;
}
