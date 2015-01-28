#include <stdlib.h>
#include <stdio.h>

#include <stumpless/exception.h>

#include "private/exception/initializer.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_initialize_by_name( void );
const char * test_initialize_constructor_failure( void );
const char * test_initialize_dictionary_failure( void );
const char * test_initialize_duplicate( void );
const char * test_initialize_incompatible_profile( void );
const char * test_initialize_malformed_structure( void );
const char * test_initialize_string_write_failure( void );
const char * test_initialize_value_profile_not_found( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( initialize_by_name )
  RUN_TEST( initialize_constructor_failure )
  RUN_TEST( initialize_dictionary_failure )
  RUN_TEST( initialize_duplicate )
  RUN_TEST( initialize_incompatible_profile )
  RUN_TEST( initialize_malformed_structure )
  RUN_TEST( initialize_string_write_failure )
  RUN_TEST( initialize_value_profile_not_found )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_initialize_by_name
( void )
{
  Exception * e = InitializeExceptionByName( "value profile not found" );
  FAIL_IF_NULL( e, "the test e could not be found" )

  e = FindExceptionByName( "value profile not found" );
  FAIL_IF_NULL( e, "after being initialized, the e was not loaded" )

  return NULL;
}

const char *
test_initialize_constructor_failure
( void )
{
  Exception * e = InitializeConstructorFailureException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "constructor failure", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_dictionary_failure
( void )
{
  Exception * e = InitializeDictionaryFailureException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "dictionary failure", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_duplicate
( void )
{
  Exception * e = InitializeDuplicateException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "duplicate", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_incompatible_profile
( void )
{
  Exception * e = InitializeIncompatibleProfileException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "incompatible profile", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_malformed_structure
( void )
{
  Exception * e = InitializeMalformedStructureException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "malformed structure", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_string_write_failure
( void )
{
  Exception * e = InitializeStringWriteFailureException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "string write failure", e->name, "the correct e was not returned from initialization" )

  return NULL;
}

const char *
test_initialize_value_profile_not_found
( void )
{
  Exception * e = InitializeValueProfileNotFoundException();
  FAIL_IF_NULL( e, "the e was not created" )

  ASSERT_STRINGS_EQUAL( "value profile not found", e->name, "the correct e was not returned from initialization" )

  return NULL;
}
