#include <stdlib.h>

#include <configuration.h>
#include <type.h>
#include <value_constructor.h>

#define CREATE_VALUE                                                           \
StumplessValue * value = malloc( sizeof( StumplessValue ) );                   \
if( value == NULL )                                                            \
  return NULL;                                                                 \
value->data = malloc( sizeof( StumplessValueData ) );                          \
if( value->data == NULL )                                                      \
  return NULL;

StumplessValue *
StumplessValueFromBoolean( const StumplessBoolean * boolean )
{
  if( boolean == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->profile = StumplessFindProfileByName( "Boolean" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->v_p = (void *) boolean;
  
  return value;
}

StumplessValue *
StumplessValueFromChar( char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_CHAR; // todo remove
  
  value->profile = StumplessFindProfileByName( "Char" );
  if( value->profile == NULL )
    return NULL;
  
  value->data->c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromDouble( double num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_DOUBLE;  // todo remove
  
  value->profile = StumplessFindProfileByName( "Double" );
  if( value->profile == NULL )
    return NULL;
  value->data->d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromFloat( float num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_FLOAT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Float" );
  if( value->profile == NULL )
    return NULL;
  value->data->f = num;
  
  return value;
}

StumplessValue *
StumplessValueFromInt( int num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_INT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Int" );
  if( value->profile == NULL )
    return NULL;
  value->data->i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLong( long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG; // todo remove
  
  value->profile = StumplessFindProfileByName( "Long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongDouble( long double num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG_DOUBLE; // todo remove
  
  value->profile = StumplessFindProfileByName( "Long Double" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongLong( long long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG_LONG; // todo remove
  
  value->profile = StumplessFindProfileByName( "Long Long" );
  if( value->profile == NULL )
    return NULL;
  value->data->l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromShort( short num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_SHORT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Short" );
  if( value->profile == NULL )
    return NULL;
  value->data->s = num;
  
  return value;
}

StumplessValue *
StumplessValueFromSignedChar( signed char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_SIGNED_CHAR; // todo remove
  
  value->profile = StumplessFindProfileByName( "Signed Char" );
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
  
  value->type = STUMPLESS_STRING; // todo remove
  
  value->profile = StumplessFindProfileByName( "String" );
  if( value->profile == NULL )
    return NULL;
  value->data->c_p = str;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedChar( unsigned char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_CHAR; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Char" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedInt( unsigned num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_INT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Int" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLong( unsigned long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_LONG; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLongLong( unsigned long long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_LONG_LONG; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Long Long" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedShort( unsigned short num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_SHORT; // todo remove
  
  value->profile = StumplessFindProfileByName( "Unsigned Short" );
  if( value->profile == NULL )
    return NULL;
  value->data->u_s = num;
  
  return value;
}
