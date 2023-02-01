#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stumpless.h>

extern "C"
int
LLVMFuzzerTestOneInput( const uint8_t *data, size_t size ) {
  char buffer[8192];
  struct stumpless_target *target;

  memset( buffer, 0, sizeof( buffer ) );
  target = stumpless_open_buffer_target( "fuzzer", buffer, sizeof( buffer ) );
  stumpless_add_message_str( target, ( char * ) data );
  stumpless_close_buffer_target( target );

  return 0;
}

