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

  char *copy = new char[size];
  memcpy( copy, data, size );
  if( size > 0 ) {
    copy[size - 1] = '\0';
  }

  target = stumpless_open_buffer_target( "fuzzer", buffer, sizeof( buffer ) );
  stumpless_add_message_str( target, copy );
  stumpless_close_buffer_target( target );
  delete[] copy;

  return 0;
}

