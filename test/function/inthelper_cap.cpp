// SPDX-License-Identifier: Apache-2.0
#include <climits>
#include <cstddef>
#include <cstring>
#include <string>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {

// make values runtime so compilers don’t fold branches
static size_t runtime_size(size_t v) {
  volatile size_t x = v;
  return x;
}

class InthelperCapBufferTest : public ::testing::Test {
protected:
  std::string backing;          // backing storage for buffer target
  stumpless_target* target;     // buffer target

  void SetUp() override {
    // Provide a reasonable backing store; 8KB is plenty for our tiny log
    backing.assign(8192, '\0');
    target = nullptr;
  }

  void TearDown() override {
    if (target) {
      stumpless_close_target(target);
      target = nullptr;
    }
    stumpless_free_all();
  }
};

TEST_F(InthelperCapBufferTest, OpenBufferWithHugeMaxLengthAndLog) {
  // Choose a huge max length that exceeds INT_MAX when representable.
#if SIZE_MAX > INT_MAX
  size_t huge = runtime_size(static_cast<size_t>(INT_MAX) + 10u);
#else
  // On platforms where size_t <= int, use a very large value still in range.
  size_t huge = runtime_size(static_cast<size_t>(INT_MAX));
#endif

  // Open a buffer target with a large declared max_length.
  // Public API is declared in include/stumpless/target/buffer.h
  // Typical signature:
  //   stumpless_target* stumpless_open_buffer_target(
  //       const char* name, char* buffer, size_t buffer_length );
  //
  // Adjust if your local header shows a slightly different name/params.
  target = stumpless_open_buffer_target("cap-test",
                                        &backing[0],
                                        huge);
  ASSERT_NOT_NULL(target);
  EXPECT_NO_ERROR;

  // Log a small entry so we exercise the write path that uses msg length.
  // (src/target/buffer.c returns cap_size_t_to_int(msg_length + 1))
  int res = stumpless_add_log(target, STUMPLESS_SEVERITY_INFO,
                              "hello cap test");
  EXPECT_GE(res, 0);
  EXPECT_NO_ERROR;

  // Sanity: the buffer should now contain at least a fragment of our message.
  // We don't assert exact syslog formatting, only that our payload appears.
  std::string view = std::string(backing.c_str());
  EXPECT_NE(std::string::npos, view.find("hello cap test"));
}

} // namespace
