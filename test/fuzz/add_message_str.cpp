#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stumpless.h>

extern "C"
int
LLVMFuzzerTestOneInput( const uint8_t *data, size_t size ) {
  char terminated_data[size+1];
  char buffer[8192];
  struct stumpless_target *target;

  memcpy( terminated_data, data, size );
  terminated_data[size] = '\0';

  target = stumpless_open_buffer_target( "fuzzer", buffer, sizeof( buffer ) );
  stumpless_add_message_str( target, terminated_data );
  stumpless_close_buffer_target( target );

  return 0;
}
