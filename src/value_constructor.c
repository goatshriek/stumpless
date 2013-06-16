#include <stdlib.h>

#include <configuration.h>
#include <type.h>
#include <value_constructor.h>

#define CREATE_VALUE                                                           \
StumplessValue * value = malloc( sizeof( StumplessValue ) );                   \
if( value == NULL )                                                            \
  return NULL;                                                                 \
value->data = malloc( sizeof( StumplessType ) );                               \
if( value->data == NULL )                                                      \
  return NULL;

StumplessValue *
StumplessValueFromBoolean( const StumplessBoolean * boolean )
{
  if( boolean == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "boolean" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->v_p = (void *) boolean;
  
  return value;
}

StumplessValue *
StumplessValueFromChar( char character )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "char" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromDouble( double num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "double" );
  if( value->profile == NULL )
    return NULL;
  value->data->d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromFloat( float num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "float" );
  if( value->profile == NULL )
    return NULL;
  value->data->f = num;
  
  return value;
}

StumplessValue *
StumplessValueFromInt( int num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "int" );
  if( value->profile == NULL )
    return NULL;
  value->data->i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLong( long num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongDouble( long double num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "long double" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongLong( long long num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "long long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromShort( short num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "short" );
  if( value->profile == NULL )
    return NULL;
  value->data->s = num;
  
  return value;
}

StumplessValue *
StumplessValueFromSignedChar( signed char character )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "signed char" );
  if( value->profile == NULL )
    return NULL;
  value->data->s_c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromString( const char * str )
{
  if( str == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "string" );
  if( value->profile == NULL )
    return NULL;
  value->data->c_p = str;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedChar( unsigned char character )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "unsigned char" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedInt( unsigned num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "unsigned int" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLong( unsigned long num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "unsigned long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLongLong( unsigned long long num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "unsigned long long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedShort( unsigned short num )
{
  CREATE_VALUE
  
  value->profile = StumplessFindValueProfileByName( "unsigned short" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_s = num;
  
  return value;
}
