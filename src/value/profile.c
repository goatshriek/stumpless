#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/value/profile.h>

#include "private/container/dictionary.h"
#include "private/type.h"
#include "private/value/profile_initializer.h"

static Dictionary *profiles = NULL;

ValueProfile *
AddValueProfile
( ValueProfile *profile )
{
  if( !profile || !profile->name )
    return profile;

  if( !profiles )
    profiles = NewDictionary();

  SetDictionaryValue( profiles, profile->name, ( void * ) profile );

  return profile;
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

  if( !profile )
    return InitializeValueProfileByName( name );

  return profile;
}
