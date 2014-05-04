#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOP_DIRECTORY
#define TOP_DIRECTORY "./";
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
  
  unsigned i = 0;
  for( i = 0; i < type_count; i++ )
    printf( types[i] );
  
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
  
  char *type = malloc( sizeof( char ) * 82 );
  if( !type )
    return 0;
  
  while( fscanf( definition_file, "struct %s {\n", type ) ){
    types[type_count] = malloc( sizeof( char ) * strlen( type ) );
    if( !types[type_count] )
      return 0;
    
    strcpy( types[type_count++], type );
  }
  
  rewind( definition_file );
  
  while( fscanf( definition_filename, "struct %s {\n", type ) ){
    types[type_count] = malloc( sizeof( char ) * strlen( type ) );
    if( !types[type_count] )
      return 0;
    
    strcpy( types[type_count++], type );
  }
  
  rewind( definition_file );
  
  while( fscanf( definition_filename, "struct %s {\n", type ) ){
    types[type_count] = malloc( sizeof( char ) * strlen( type ) );
    if( !types[type_count] )
      return 0;
    
    strcpy( types[type_count++], type );
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
