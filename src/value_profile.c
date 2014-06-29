#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/type.h"
#include "private/value_profile.h"
#include "private/value_profile_initializer.h"

static Dictionary * profiles = NULL;

Status *
AddValueProfile
( ValueProfile * profile )
{
  if( profile == NULL || profile->name == NULL )
    return NULL;
  
  if( profiles == NULL ){
    profiles = NewDictionary();
    
    if( profiles == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  void * value = ( void * ) profile;
  if( SetDictionaryValue( profiles, profile->name, value ) == NULL )
    return NULL;
  
  return NULL;
}

ValueProfile *
FindValueProfileByName
( const char * name )
{
  if( profiles == NULL ){
    profiles = NewDictionary();
    
    if( profiles == NULL )
      return NULL;
  }
  
  ValueProfile * profile = GetDictionaryValue( profiles, name );
  
  if( profile == NULL ){
    if( InitializeValueProfileByName( name ) != NULL )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }
  
  return profile;
}
