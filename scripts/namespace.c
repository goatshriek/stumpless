#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/utility/string.h"

#ifndef TOP_DIRECTORY
#define TOP_DIRECTORY "./"
#endif

static const char *prefix;

static char *types[200];
static int type_count = 0;

// todo read in full filenames (with directory) from config file if possible
static const char *definition_filename = TOP_DIRECTORY "include/stumpless/type/definition.h";
static const char *input_definition_filename = TOP_DIRECTORY "include/stumpless/type/definition.h.in";
static const char *declaration_filename = TOP_DIRECTORY "include/stumpless/type/declaration.h";
static const char *input_declaration_filename = TOP_DIRECTORY "include/stumpless/type/declaration.h.in";

static const char *input_private_type_declarations = TOP_DIRECTORY "include/private/type/declaration.h.in";
static const char *private_type_declarations = TOP_DIRECTORY "include/private/type/declaration.h";

static const char *public_include_dir = TOP_DIRECTORY "include/stumpless/";
static const char *stumpless_src_dir = TOP_DIRECTORY "src/stumpless/";

int GatherTypes( void );
int GenerateDeclarations( void );
int GenerateDefinitions( void );
int GenerateTypedefs( void );
int GenerateHeadersAndSources( void );
char * ReplaceTypes( char * );

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

  if( !GenerateDeclarations() )
    return EXIT_FAILURE;

  if( !GenerateDefinitions() )
    return EXIT_FAILURE;

  if( !GenerateTypedefs() )
    return EXIT_FAILURE;

  if( !GenerateHeadersAndSources() )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

// todo refactor to remove buffer overflow vulnerability
int
GatherTypes
( void )
{
  FILE *declaration_file = fopen( declaration_filename, "r" );
  if( !declaration_file )
    return 0;

  char type[82];
  type[0] = type[81] = '\0';
  char word[82];
  word[0] = word[81] = '\0';

  unsigned short next = 0;
  while( fscanf( declaration_file, "%81s %81[^;];", type, word ) == 2 ){
    if( strcmp( type, "struct" ) == 0
        || strcmp( type, "enum" ) == 0
        || strcmp( type, "union" ) == 0 ){
      types[type_count] = malloc( sizeof( char ) * strlen( word ) );
      if( !types[type_count] )
        return 0;

      if( type_count > 200 ){
        fputs( "more than 200 types were detected", stderr );
        return 0;
      }

      strcpy( types[type_count++], word );
    }
  }

  fclose( declaration_file );

  return 1;
}

int
GenerateDefinitions
( void )
{
  rename( definition_filename, input_definition_filename );

  FILE *definition_file = fopen( input_definition_filename, "r" );
  if( !definition_file )
    return 0;

  FILE *definition_output_file = fopen( definition_filename, "w" );
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
GenerateDeclarations
( void )
{
  rename( declaration_filename, input_declaration_filename );

  FILE *declaration_file = fopen( input_declaration_filename, "r" );
  if( !declaration_file )
    return 0;

  FILE *declaration_output_file = fopen( declaration_filename, "w" );
  if( !declaration_output_file )
    return 0;

  char word[82];
  unsigned i;
  int character;
  while( ( character = fgetc( declaration_file ) ) != EOF ){
    if( isspace( character ) ){
      fputc( character, declaration_output_file );
      continue;
    }

    for( i = 0; !isspace( character ) && i < 82; i++ ){
      word[i] = character;
      character = fgetc( declaration_file );
    }
    word[i] = '\0';

    for( i = 0; i < type_count; i++ ){
      if( strcmp( types[i], word ) == 0 ){
        fputs( prefix, declaration_output_file );
        break;
      }
    }
    fputs( word, declaration_output_file );
    fputc( character, declaration_output_file );
  }

  fclose( declaration_file );
  fclose( declaration_output_file );

  return 1;
}

int
GenerateTypedefs
( void )
{
  rename( private_type_declarations, input_private_type_declarations );

  FILE *previous_declarations = fopen( input_private_type_declarations, "r" );
  if( !previous_declarations )
    return 0;

  FILE *new_declarations = fopen( private_type_declarations, "w" );
  if( !new_declarations )
    return 0;

  char line[200];
  const char *endif = "#endif";
  while( !feof( previous_declarations ) ){
    fgets( line, 200, previous_declarations );
    if( strstr( line, endif ) == line ){
      break;
    } else {
      fputs( line, new_declarations );
    }
  }

  fputc( '\n', new_declarations );

  unsigned i;
  for( i = 0; i < type_count; i++ ){
    fprintf( new_declarations, "typedef Stumpless%s %s\n", types[i], types[i] );
  }

  fputc( '\n', new_declarations );
  fputs( endif, new_declarations );

  fclose( previous_declarations );
  fclose( new_declarations );

  return 1;
}

int
GenerateHeadersAndSources
( void )
{
  const char *files[1];
  unsigned file_count = 1;

  files[0] = "value";

  char input_header[200];
  strncpy( input_header, public_include_dir, 99 );
  input_header[99] = '\0';
  char *input_header_start = input_header + strlen( input_header );

  char new_header[200];
  strncpy( new_header, public_include_dir, 99 );
  new_header[99] = '\0';
  char *new_header_start = new_header + strlen( new_header );

  char source[200];
  strncpy( source, stumpless_src_dir, 99 );
  source[99] = '\0';
  char *source_start = source + strlen( source );

  char line[500];
  char one_ago[200];
  char two_ago[200];
  char temp_filename[200];
  unsigned parameter_count;
  char parameter_name[100];
  FILE *input_header_file, *new_header_file, *source_file;
  unsigned i, j;
  for( i = 0; i < file_count; i++ ){
    strcpy( temp_filename, files[i] );
    strncpy( input_header_start, strncat( temp_filename, ".h.in", 6 ), 99 );
    input_header_start[99] = '\0';

    strcpy( temp_filename, files[i] );
    strncpy( new_header_start, strncat( temp_filename, ".h", 3 ), 99 );
    new_header_start[99] = '\0';

    strcpy( temp_filename, files[i] );
    strncpy( source_start, strncat( temp_filename, ".c", 3 ), 99 );
    source_start[99] = '\0';

    rename( new_header, input_header );

    input_header_file = fopen( input_header, "r" );
    if( !input_header_file )
      return 0;

    new_header_file = fopen( new_header, "w" );
    if( !new_header_file )
      return 0;

    source_file = fopen( source, "w" );
    if( !source_file )
      return 0;

    fputs( "#include <stumpless/", source_file );
    fputs( files[i], source_file );
    fputs( ".h>\n#include \"private", source_file );
    fputs( files[i], source_file );
    fputs( ".h\n\n", source_file );

    while( !feof( input_header_file ) ){
      fgets( line, 80, input_header_file );
      ReplaceTypes( line );
      fputs( line, new_header_file );

      if( line[0] == '(' ){
        parameter_count = 0;
        while( strstr( line, "," ) ){
          sprintf( parameter_name, " param%i$", parameter_count++ );
          replace_first_string( line, ",", parameter_name );
        }
        replace_char( line, '$', ',' );

        if( strcmp( line, "( void )" ) == 0 ){
          replace_first_string( line, ");", ")" );
        } else {
          sprintf( parameter_name, " param%i )", parameter_count++ );
          replace_first_string( line, ")", parameter_name );
        }

        fputs( two_ago, source_file );
        fputs( one_ago, source_file );
        fputs( line, source_file );
        fputs( "{\n  return ", source_file );
        fputs( one_ago, source_file );
        fputs( "(", source_file );
        for( j = 0; j < parameter_count; j++ ){
          fprintf( source_file, "param%i ", j );
          if( j < parameter_count - 1 )
            fputs( ", ", source_file );
        }
        fputs( ");\n}", source_file );
      }

      strncpy( two_ago, one_ago, 199 );
      strncpy( one_ago, line, 199 );
    }

    fclose( input_header_file );
    fclose( new_header_file );
    fclose( source_file );
  }

  return 1;
}

char *
ReplaceTypes
( char *str )
{
  char new_type[100];
  strncpy( new_type, prefix, 50 );
  new_type[50] = '\0';
  new_type[99] = '\0';
  char *new_type_placeholder = new_type + strlen( new_type );

  unsigned i;
  for( i = 0; i < type_count; i++ ){
    strncpy( new_type_placeholder, types[i], 49 );
    replace_string( str, types[i], new_type );
  }

  return str;
}
