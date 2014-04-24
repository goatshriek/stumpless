#include <stdio.h>
#include <stdlib.h>

const char * prefix;
static char *types[];

int ReadTypes( void );
int GenerateTypedefs( void );
int GenerateStumplessHeader( void );

int
main
( int argc, char *argv[] )
{
  if( argc < 1 )
    prefix = "Stumpless";
  else
    prefix = argv[0];
  
  if( !ReadTypes() )
    return EXIT_FAILURE;
  
  if( !GenerateTypedefs() )
    return EXIT_FAILURE;
  
  if( !GenerateStumplessHeader() )
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}

int
ReadTypes
( void )
{
  // todo read in full filename from config file if possible
  const char *type_filename = "include/stumpless/type.h";
  
  FILE *type_file = fopen( type_filename, "r" );
  if( !type_file )
    return NULL;
  
  return 0;
}

int
GenerateTypedefs
( void )
{
  return 0;
}

// iterate through non-stumpless src files
// generate stumpless src files
// generate stumpless include files

int
GenerateStumplessHeader
( void )
{
  return 0;
}
