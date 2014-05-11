#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOP_DIRECTORY
#define TOP_DIRECTORY "./"
#endif

static const char *prefix;
static char *types[100];
static int type_count = 0;

// todo read in full filename (with directory) from config file if possible
static const char *definition_filename = TOP_DIRECTORY "include/stumpless/type/definition.h.in";

int ReadTypes( void );
int GenerateTypedefs( void );
int GenerateStumplessHeader( void );

int
main
( int argc, char *argv[] )
{
  if( argc < 2 )
    prefix = "Stumpless";
  else
    prefix = argv[1];
  
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
  FILE *definition_file = fopen( definition_filename, "r" );
  if( !definition_file )
    return 0;
  
  char word[82];
  word[0] = '\0';
  
  unsigned short next;
  while( fscanf( definition_file, "%s", word ) == 1 ){
    if( next ){
      types[type_count] = malloc( sizeof( char ) * strlen( word ) );
      if( !types[type_count] )
        return 0;
      
      strcpy( types[type_count++], word );
      
      next = 0;
    }
    
    if( strcmp( word, "struct" ) == 0
        || strcmp( word, "enum" ) == 0
        || strcmp( word, "union" ) == 0 )
      next = 1;
  }
  
  fclose( definition_file );
  
  return 1;
}

int
GenerateTypedefs
( void )
{
  FILE *definition_file = fopen( definition_filename, "r" );
  if( !definition_file )
    return 0;
  
  FILE *definition_output_file = fopen( TOP_DIRECTORY "include/stumpless/type/definition.h", "w" );
  if( !definition_output_file )
    return 0;
  
  char word[82];
  unsigned i;
  int character = fgetc( definition_file );
  while( ( character = fgetc( definition_file ) ) != EOF ){
    if( isspace( character ) ){
      fputc( character, definition_output_file );
      continue;
    }
    
    for( i = 0; !isspace( character ) || i > 81; i++ ){
      word[i] = character;
      character = fgetc( definition_file );
    }
    word[i] = '\0';
    
    for( i = 0; i < type_count; i++ ){
      if( strcmp( types[i], word ) == 0 ){
        fputs( prefix, definition_output_file );
        break;
      }
    }
    fputs( word, definition_output_file );
    fputc( character, definition_output_file );
  }
  
  fclose( definition_file );
  fclose( definition_output_file );
  
  return 1;
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
