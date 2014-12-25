#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/level.h"
#include "test/function/level.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;
 
  TEST( AlertLevel)
  //TEST( CriticalLevel)
  //TEST( DebugLevel)
  //TEST( EmergencyLevel)
  //TEST( ErrorLevel)
  //TEST( InformationalLevel)
  TEST( LevelToString)
  //TEST( NoticeLevel)
  //TEST( WarningLevel)
   
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAlertLevel
( void )
{
  Level *level = FindLevelByName( "alert" );
  if( !level )
    return "the alert Level could not be found";
  
  ASSERT_STRINGS_EQUAL( "alert", level->name, "the alert Level did not have the appropriate name" )

  return NULL;
}

const char *
TestLevelToString
( void )
{
  char *description = LevelToString( NULL );
  if( description )
    return "the description was not null for a null pointer";
  
  Level *level = BuildLevel();
  description = LevelToString( level );
  if( !description )
    return "the description string was null for a non-null level pointer";
  if( !strstr( description, "Test Level" ) )
    return "the description did not contain the level's name";
  
  return NULL;
}
