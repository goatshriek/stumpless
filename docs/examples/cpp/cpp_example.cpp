#include <FileTarget.hpp>
#include <stumpless.h>

using namespace stumpless;

int
main( int argc, char **argv ) {

  // creates a log target aimed at the given file
  FileTarget file_logger ( "cpp_example.log",
                           STUMPLESS_OPTION_NONE,
                           STUMPLESS_FACILITY_USER );

}
