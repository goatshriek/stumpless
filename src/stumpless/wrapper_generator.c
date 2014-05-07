#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOP_DIRECTORY
#define TOP_DIRECTORY "./"
#endif

const char *prefix;
static char *types[100];
int type_count = 0;

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

// todo refactor to remove buffer overflow vulnerability
int
ReadTypes
( void )
{
  // todo read in full filename (with directory) from config file if possible
  const char *definition_filename = TOP_DIRECTORY "include/stumpless/type/definition.h.in";
  
  FILE *definition_file = fopen( definition_filename, "r" );
  if( !definition_file )
    return 0;
  
  char type[82];
  type[0] = '\0';
  
  unsigned short next;
  while( fscanf( definition_file, "%s", type ) == 1 ){
    if( next ){
      types[type_count] = malloc( sizeof( char ) * strlen( type ) );
      if( !types[type_count] )
        return 0;
      
      strcpy( types[type_count++], type );
      
      next = 0;
    }
    
    if( strcmp( type, "struct" ) == 0 || strcmp( type, "enum" ) == 0 || strcmp( type, "union" ) == 0 )
      next = 1;
  }
  
  fclose( definition_file );
  free( type );
  
  return 1;
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
