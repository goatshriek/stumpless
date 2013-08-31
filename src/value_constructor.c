#include <stdlib.h>

#include "private/configuration.h"
#include "private/type.h"
#include "private/value_constructor.h"

#define CREATE_VALUE                                                           \
Value * value = malloc( sizeof( Value ) );                                     \
if( value == NULL )                                                            \
  return NULL;                                                                 \
value->data = malloc( sizeof( Type ) );                                        \
if( value->data == NULL )                                                      \
  return NULL;

Value *
ValueFromBoolean( const Boolean * boolean )
{
  if( boolean == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "boolean" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->v_p = (void *) boolean;
  
  return value;
}

Value *
ValueFromChar( char character )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "char" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->c = character;
  
  return value;
}

Value *
ValueFromDouble( double num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "double" );
  if( value->profile == NULL )
    return NULL;
  value->data->d = num;
  
  return value;
}

Value *
ValueFromFloat( float num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "float" );
  if( value->profile == NULL )
    return NULL;
  value->data->f = num;
  
  return value;
}

Value *
ValueFromInt( int num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "int" );
  if( value->profile == NULL )
    return NULL;
  value->data->i = num;
  
  return value;
}

Value *
ValueFromLong( long num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l = num;
  
  return value;
}

Value *
ValueFromLongDouble( long double num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "long double" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_d = num;
  
  return value;
}

Value *
ValueFromLongLong( long long num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "long long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_l = num;
  
  return value;
}

Value *
ValueFromShort( short num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "short" );
  if( value->profile == NULL )
    return NULL;
  value->data->s = num;
  
  return value;
}

Value *
ValueFromSignedChar( signed char character )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "signed char" );
  if( value->profile == NULL )
    return NULL;
  value->data->s_c = character;
  
  return value;
}

Value *
ValueFromString( const char * str )
{
  if( str == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "string" );
  if( value->profile == NULL )
    return NULL;
  value->data->c_p = str;
  
  return value;
}

Value *
ValueFromUnsignedChar( unsigned char character )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "unsigned char" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_c = character;
  
  return value;
}

Value *
ValueFromUnsignedInt( unsigned num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "unsigned int" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_i = num;
  
  return value;
}

Value *
ValueFromUnsignedLong( unsigned long num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "unsigned long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l = num;
  
  return value;
}

Value *
ValueFromUnsignedLongLong( unsigned long long num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "unsigned long long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l_l = num;
  
  return value;
}

Value *
ValueFromUnsignedShort( unsigned short num )
{
  CREATE_VALUE
  
  value->profile = FindValueProfileByName( "unsigned short" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_s = num;
  
  return value;
}
