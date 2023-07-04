#include <cstddef>
#include <cstdlib>
#include <stumpless.h>
#include <stumpless.hpp>
#include <iostream>

using namespace stumpless;

int
main( int argc, char **argv ) {

  // creates a log target for the file `cpp_example.log`
  // the file will be created if it does not exist
  FileTarget file_logger( "cpp_example.log" );

  // logs the given message to the file
  file_logger.Log( "she just made ANOTHER u-turn" );
  // the entry will look like this:
  // <14>1 2020-05-15T16:28:56.266031Z Angus - 4484 - - she just made ANOTHER u-turn
  // 'Angus' is the name of the system this was logged on
  // the three '-' characters are the app name, the message id, and the structured data,
  // which were all empty here
  // '4484' is PID of the process that logged this message

  // logs the given message to the file at the given priority
  file_logger.Log( Facility::NEWS, Severity::EMERGENCY,
                   "Helen's lost again!!!" );
  // the entry will look like this:
  // <56>1 2020-05-15T16:28:56.267113Z Angus - 4484 - - Helen's lost again!!!

  // logs the given message and format strings to the file
  // you can use format strings with the previous forms as well if you want to
  file_logger.Log( "she's gotten lost %d times in the last %d days", 25, 3 );
  // the entry will look like this:
  // <14>1 2020-05-15T16:28:56.267128Z Angus - 4484 - - she's gotten lost 25 times in the last 3 days

  // creates an Entry for a common event
  Entry up_to_code( Facility::USER,
                    Severity::INFO,
                    "cpp-demo-app",
                    "up-to-code",
                    "is it up to code?" );

  // makes an element named 'subject' and adds it to the entry
  Element item( "subject" );
  up_to_code.AddElement( item );

  // adds a few parameters to the element
  Param name( "name", "baked alaska" );
  Param result( "result", "not-up-to-code" );

  // most `Add` and `Set` methods can be chained together
  item.AddParam( name ).AddParam( result );

  // writing an entry to the log file
  file_logger.Log( up_to_code );
  // <14>1 2020-05-05T19:55:48.368156Z Angus cpp-demo-app 4484 up-to-code [subject name="baked alaska" result="not-up-to-code"] is it up to code?

  // error checking can be done using standard try/catch blocks
  try {
    file_logger.SetDefaultAppName( NULL );

  // you MUST catch a pointer to StumplessException, like this
  } catch( StumplessException *e ) {

    // you can check the error id of the exception to see what the actual
    // problem was
    if( e->GetErrorId() == ErrorId::ARGUMENT_EMPTY ) {
      std::cout << "the app name was NULL!" << std::endl;
    }
  }

  // use the same headers and values for support checks:
#ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
  // constants are added to relevant classes
  // this gives them type safety and namespace scoping!
  std::cout << "logging to " << SocketTarget::DEFAULT_SOCKET << " by default" << std::endl;
#else
  std::cout << "socket targets aren't supported by this build" << std::endl;
#endif

  return EXIT_SUCCESS;
}
