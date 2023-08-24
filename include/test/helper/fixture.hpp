/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2023 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __STUMPLESS_TEST_HELPER_FIXTURE_HPP
#  define __STUMPLESS_TEST_HELPER_FIXTURE_HPP

#  include <cstdlib>
#  include <gtest/gtest.h>
#  include <string>
#  include <stumpless.h>

#  define BUFFER_TARGET_FIXTURE_CLASS( CLASS_NAME )                            \
class CLASS_NAME : public::testing::Test {                                     \
protected:                                                                     \
  char buffer[8192];                                                           \
  struct stumpless_target *target;                                             \
  struct stumpless_entry *basic_entry;                                         \
  const char *basic_message;                                                   \
                                                                               \
  virtual void                                                                 \
  SetUp( void ) {                                                              \
    buffer[0] = '\0';                                                          \
    target = stumpless_open_buffer_target( "info level testing",               \
                                           buffer,                             \
                                           sizeof( buffer ) );                 \
                                                                               \
    stumpless_set_target_default_app_name( target, "info-level-test" );        \
    stumpless_set_target_default_msgid( target, "default-message" );           \
    basic_entry = create_entry(  );                                            \
    basic_message = stumpless_get_entry_message( basic_entry );                \
  }                                                                            \
                                                                               \
  virtual void                                                                 \
  TearDown( void ) {                                                           \
    free( ( void * ) basic_message );                                          \
    stumpless_destroy_entry_and_contents( basic_entry );                       \
    stumpless_close_buffer_target( target );                                   \
  }                                                                            \
}

struct stumpless_entry *
create_empty_entry( void );

struct stumpless_entry *
create_entry( void );

/**
 * Returns a buffer holding the contents of the fuzz corpus file at the named
 * location in the test/corpora folder. For example, a name of "message/ascii"
 * will return the contents of the test/corpora/message/ascii file.
 *
 * The returned buffer must be destroyed with the delete[] operator when it is
 * no longer needed to avoid memory leaks.
 *
 * @param name The corpus file name.
 *
 * @return a buffer holding the contents of the file, or NULL if an error
 * occurred.
 */
const char *
load_corpus( const std::string& name );

struct stumpless_test_data {
  int length;
  char **test_strings;
};

/**
 * Returns stumpless_test_data holding the contents of all the files at the named
 * location in the test/corpora folder. For example, a name of "invalid_param_name"
 * will return the contents of all the files under test/corpora/invalid_param_name 
 * directory in the form of an array.
 *
 * The allocated memory for test_strings must be safely freed up using free() 
 * and the buffer content (returned from load_corpus method) should also be 
 * destroyed using delete[] when no longer needed to avoid memory leaks.
 *
 * @param name The directory name.
 *
 * @return stumpless_test_data holding the test_strings pointing to contents of the 
 * directory as an array and corresponding size stored as length.
 */
stumpless_test_data 
load_corpus_folder( const std::string& name );

#endif /* __STUMPLESS_TEST_HELPER_FIXTURE_HPP */
