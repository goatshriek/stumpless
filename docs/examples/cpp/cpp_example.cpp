#include <Element.hpp>
#include <Entry.hpp>
#include <Param.hpp>
#include <FileTarget.hpp>
#include <stumpless.h>

#include <iostream>

using namespace stumplesscpp;

int
main( int argc, char **argv ) {

  // creates a log target for the file `cpp_example.log`
  // the file will be created if it does not exist
  FileTarget file_logger( "cpp_example.log",
                          STUMPLESS_OPTION_NONE,
                          STUMPLESS_FACILITY_USER );

  // creates an entry with the given message and adds it to the file
  file_logger.AddMessage( "she just drank ANOTHER bloody mary" );
  // the entry will look like this:

  // creates an Entry for a common event
  Entry up_to_code( STUMPLESS_FACILITY_USER,
                    STUMPLESS_SEVERITY_INFO,
                    "cpp-demo-app",
                    "up-to-code",
                    "is it up to code?" );
  Element item( "subject" );
  up_to_code.AddElement(item);

  Param name("name", "baked alaska");
  Param result("result", "not-up-to-code");

  // most `Add` and `Set` methods can be chained together
  item.AddParam(name).AddParam(result);

  // writing an entry to the log file
  file_logger.Log( up_to_code );
  // the entry will look like this:

  stumpless_perror( "fail!" );

  return EXIT_SUCCESS;
}
