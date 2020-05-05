#include <Element.hpp>
#include <Entry.hpp>
#include <Param.hpp>
#include <FileTarget.hpp>
#include <SocketTarget.hpp>
#include <stumpless.h>
#include <StumplessException.hpp>
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

  // makes an element named 'subject' and adds it to the entry
  Element item( "subject" );
  up_to_code.AddElement(item);

  // adds a few parameters to the element
  Param name("name", "baked alaska");
  Param result("result", "not-up-to-code");

  // most `Add` and `Set` methods can be chained together
  item.AddParam(name).AddParam(result);

  // writing an entry to the log file
  file_logger.Log( up_to_code );
  // the entry will look like this:

  // error checking can be done using standard try/catch blocks
  try {
    file_logger.Log( NULL );

  // you MUST catch a pointer to StumplessException, like this
  } catch( StumplessException *e ) {
    std::cout << "there was an empty argument in that call!" << std::endl;
  }

  // use the same headers and values for support checks:
  if( STUMPLESS_SOCKET_TARGETS_SUPPORTED ) {
    // constants are added to relevant classes
    // this gives them type safety and namespace scoping!
    std::cout << "logging to " << SocketTarget::DEFAULT_SOCKET << " by default" << std::endl;
  } else {
    std::cout << "socket targets aren't supported by this build" << std::endl;
  }

  return EXIT_SUCCESS;
}
