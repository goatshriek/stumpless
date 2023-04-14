#include <cstddef>
#include <cstdint>
#include <string>
#include <stumpless.h>

extern "C"
int
LLVMFuzzerTestOneInput( const uint8_t *data, size_t size ) {
  std::string fuzz_str ( ( char * ) data, size );
  char buffer[8192];
  struct stumpless_target *target;

  // Function will send message to the last opened target.
  target = stumpless_open_buffer_target( "fuzzer", buffer, sizeof( buffer ) );
  stump_str( fuzz_str.c_str(  ) );
  stumpless_close_buffer_target( target );

  return 0;
}
