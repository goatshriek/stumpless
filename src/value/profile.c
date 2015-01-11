#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/value/profile.h>

#include "private/container/dictionary.h"
#include "private/type.h"
#include "private/value/profile_initializer.h"

static Dictionary *profiles = NULL;

Exception *
AddValueProfile
( ValueProfile *profile )
{
  void *value;

  if( !profile || !profile->name )
    return NULL;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return RaiseException( "constructor failure" );
  }

  value = ( void * ) profile;
  if( !SetDictionaryValue( profiles, profile->name, value ) )
    return NULL;

  return NULL;
}

ValueProfile *
FindValueProfileByName
( const char *name )
{
  ValueProfile *profile;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return NULL;
  }

  profile = GetDictionaryValue( profiles, name );

  if( !profile ){
    if( InitializeValueProfileByName( name ) )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }

  return profile;
}
