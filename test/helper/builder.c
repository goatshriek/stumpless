#include "builder.h"

StumplessEvent *
BuildEvent( void )
{
  StumplessEvent * event = malloc( sizeof( StumplessEvent ) );
  if( event == NULL )
    return NULL;
  
  event->name = "Test Event";
  
  event->level = BuildLevel();
  if( event->level == NULL )
    return NULL;
  
  event->attributes = BuildEventAttributeList();
  if( event->attributes == NULL )
    return NULL;
  event->attribute_count = 5;
  
  return event;
}

StumplessEventAttribute **
BuildEventAttributeList( void )
{
  StumplessEventAttribute ** list;
  list = malloc( sizeof( StumplessEventAttribute * ) * 5 );
  if( list == NULL )
    return NULL;
  
  StumplessEventAttribute * attr_0;
  attr_0 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_0 == NULL )
    return NULL;
  attr_0->name = "Test Attribute 0";
  attr_0->default_value = StumplessValueFromString( "default value" );
  
  StumplessEventAttribute * attr_1;
  attr_1 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_1 == NULL )
    return NULL;
  attr_1->name = NULL;
  attr_1->default_value = StumplessValueFromString( "default value" );
  
  StumplessEventAttribute * attr_2;
  attr_2 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_2 == NULL )
    return NULL;
  attr_2->name = "Test Attribute 0";
  attr_2->default_value = NULL;
  
  StumplessEventAttribute * attr_3;
  attr_3 = malloc( sizeof( StumplessEventAttribute ) );
  if( attr_3 == NULL )
    return NULL;
  attr_3->name = NULL;
  attr_3->default_value = NULL;
  
  list[0] = attr_0;
  list[1] = attr_1;
  list[2] = attr_2;
  list[3] = attr_3;
  list[4] = NULL;
  
  return list;
}

StumplessLevel *
BuildLevel( void )
{
  StumplessLevel * level = malloc( sizeof( StumplessLevel ) ) ;
  if( level == NULL )
    return NULL;
  
  level->name = "Test Level";
  level->value = 42;
  
  return level;
}
