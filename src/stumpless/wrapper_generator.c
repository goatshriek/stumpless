#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TOP_DIRECTORY
#define TOP_DIRECTORY "./"
#endif

static const char *prefix;

static char *types[100];
static int type_count = 0;

static char *functions[300];
static int function_count = 0;

// todo read in full filenames (with directory) from config file if possible
static const char *definition_filename = TOP_DIRECTORY "include/stumpless/type/definition.h.in";
static const char *private_includes = TOP_DIRECTORY "include/private/";

int GatherTypes( void );
int GenerateTypedefs( void );
int GatherStumplessFunctions( void );
int GenerateStumplessHeaders( void );
int GenerateStumplessSources( void );

int
main
( int argc, char *argv[] )
{
  if( argc < 2 )
    prefix = "Stumpless";
  else
    prefix = argv[1];
  
  if( !GatherTypes() )
    return EXIT_FAILURE;
  
  //if( !GenerateTypedefs() )
  //  return EXIT_FAILURE;
  
  if( !GatherStumplessFunctions() )
    return EXIT_FAILURE;
  
  if( !GenerateStumplessHeaders() )
    return EXIT_FAILURE;
  
  if( !GenerateStumplessHeaders() )
    return EXIT_FAILURE;
  
  if( !GenerateStumplessSources() )
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}

// todo refactor to remove buffer overflow vulnerability
int
GatherTypes
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
  int character;
  while( ( character = fgetc( definition_file ) ) != EOF ){
    if( isspace( character ) ){
      fputc( character, definition_output_file );
      continue;
    }
    
    for( i = 0; !isspace( character ) && i < 82; i++ ){
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

int
GatherStumplessFunctions
( void )
{
  // todo make file retrieval dynamic
  // be sure to exclude the type directory
  const char *files[2];
  unsigned file_count = 2;
  files[0] = "adapter.h";
  files[1] = "handler/stream.h";
  
  // read through each file
  unsigned i, line_length;
  char filename[100];
  char function[100];
  char line[100];
  FILE *file;
  for( i = 0; i < file_count; i++ ){
    filename[0] = '\0';
    strncat( filename, private_includes, 50 );
    strncat( filename, files[i], 49 );
    filename[99] = '\0';
    file = fopen( filename, "r" );
    if( !file ){
      printf( "couldn't open header file: %s\n", filename  );
      return 0;
    }
    
    while( fgets( line, 100, file ) ){
      if( line[0] == '\n' ){
        fgets( line, 100, file );
        fgets( line, 100, file );
        
        if( line[0] == '\n' || line[0] == '#' )
          continue;
        
        line_length = strlen( line );
        functions[function_count] = malloc( sizeof( char ) * line_length );
        if( !functions[function_count] ){
          printf( "couldn't allocate memory for the %d function name\n", function_count+1 );
          return 0;
        }
        
        strncpy( functions[function_count], line, line_length );
        functions[function_count][line_length-1] = '\0';
        printf( "%s\n", functions[function_count] );
        function_count++;
      }
    }
  }
  
  return 1;
}

int
GenerateStumplessHeaders
( void )
{
  return 0;
}

int
GenerateStumplessSources
( void )
{
  return 0;
}
