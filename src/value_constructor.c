#include <type.h>
#include <value_constructor.h>

StumplessValue *
StumplessValueFromChar( char character )
{
  return NULL;
}

StumplessValue *
StumplessValueFromDouble( double num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromFloat( float num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromInt( int num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromLong( long num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromLongDouble( long double num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromLongLong( long long num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromShort( short num )
{
  return NULL;
}


StumplessValue *
StumplessValueFromString( const char * str )
{
  if( str == NULL )
    return NULL;
  
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
 
  value->type = STUMPLESS_STRING;
  value->data->c_p = str;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedChar( unsigned char character )
{
  return NULL;
}

StumplessValue *
StumplessValueFromUnsignedInt( unsigned num )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->type = STUMPLESS_UNSIGNED_INT;
  value->data->u_i = num;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedLong( unsigned long num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromUnsignedLongLong( unsigned long long num )
{
  return NULL;
}

StumplessValue *
StumplessValueFromUnsignedShort( unsigned short num )
{
  return NULL;
}
