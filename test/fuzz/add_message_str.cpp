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

  target = stumpless_open_buffer_target( "fuzzer", buffer, sizeof( buffer ) );
  stumpless_add_message_str( target, fuzz_str.c_str(  ) );
  stumpless_close_buffer_target( target );

  return 0;
}
