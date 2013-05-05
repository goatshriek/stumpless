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
StumplessValueFromChar( char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_CHAR;
  value->data->c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromDouble( double num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_DOUBLE;
  value->data->d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromFloat( float num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_FLOAT;
  value->data->f = num;
  
  return value;
}

StumplessValue *
StumplessValueFromInt( int num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_INT;
  value->data->i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLong( long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG;
  value->data->l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongDouble( long double num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG_DOUBLE;
  value->data->l_d = num;
  
  return value;
}

StumplessValue *
StumplessValueFromLongLong( long long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_LONG_LONG;
  value->data->l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromShort( short num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_SHORT;
  value->data->s = num;
  
  return value;
}

StumplessValue *
StumplessValueFromSignedChar( signed char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_SIGNED_CHAR;
  value->data->s_c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromString( const char * str )
{
  if( str == NULL )
    return NULL;
  
  CREATE_VALUE
  
  value->type = STUMPLESS_STRING;
  value->data->c_p = str;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedChar( unsigned char character )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_CHAR;
  value->data->u_c = character;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedInt( unsigned num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_INT;
  value->data->u_i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLong( unsigned long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_LONG;
  value->data->u_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLongLong( unsigned long long num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_LONG_LONG;
  value->data->u_l_l = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedShort( unsigned short num )
{
  CREATE_VALUE
  
  value->type = STUMPLESS_UNSIGNED_SHORT;
  value->data->u_s = num;
  
  return value;
}
