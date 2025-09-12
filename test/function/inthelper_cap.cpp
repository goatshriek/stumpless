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

class InthelperCapParamTest : public ::testing::Test {
protected:
  stumpless_param* param = nullptr;

  void SetUp() override {
    param = stumpless_new_param("name", "value");
    ASSERT_NOT_NULL(param);
  }

  void TearDown() override {
    if (param) {
      stumpless_destroy_param(param);
      param = nullptr;
    }
    stumpless_free_all();
  }
};

TEST_F(InthelperCapParamTest, IntoString_SmallMax) {
  char buf[64];
  memset(buf, 0, sizeof(buf));

  size_t written = stumpless_param_into_string(param, buf, sizeof(buf));
  ASSERT_GT(written, 0u);
  EXPECT_NO_ERROR;

  std::string s(buf);
  EXPECT_NE(s.find("name=\"value\""), std::string::npos);
}

TEST_F(InthelperCapParamTest, IntoString_HugeMaxCapsToIntMax) {
#if SIZE_MAX > INT_MAX
  size_t huge = static_cast<size_t>(INT_MAX) + 1u;
#else
  size_t huge = static_cast<size_t>(INT_MAX); // platform fallback
#endif

  std::string big(4096, '\0'); // plenty for our tiny output
  size_t written = stumpless_param_into_string(param, big.data(), huge);
  ASSERT_GT(written, 0u);
  EXPECT_NO_ERROR;

  std::string s(big.c_str());
  EXPECT_NE(s.find("name=\"value\""), std::string::npos);
}

} // namespace
