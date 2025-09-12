// SPDX-License-Identifier: Apache-2.0
#include <climits>
#include <cstddef>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {

class InthelperPublicTest : public ::testing::Test {
protected:
  stumpless_element* element = nullptr;

  void SetUp() override {
    element = stumpless_new_element("e");
    ASSERT_NOT_NULL(element);
    stumpless_param* p = stumpless_new_param("k", "v");
    ASSERT_NOT_NULL(p);
    const stumpless_element* add_res = stumpless_add_param(element, p);
    ASSERT_EQ(add_res, element);
    EXPECT_NO_ERROR;
  }

  void TearDown() override {
    if (element) {
      stumpless_destroy_element_and_contents(element);
      element = nullptr;
    }
    stumpless_free_all();
  }
};

TEST_F(InthelperPublicTest, GetParamByIndex_WithinRange) {
  const stumpless_param* param = stumpless_get_param_by_index(element, 0u);
  ASSERT_NOT_NULL(param);
  EXPECT_NO_ERROR;
}

TEST_F(InthelperPublicTest, GetParamByIndex_TooLargeIndex) {
#if SIZE_MAX > INT_MAX
  size_t huge = static_cast<size_t>(INT_MAX) + 1u;
#else
  size_t huge = static_cast<size_t>(INT_MAX); // platform fallback
#endif
  const stumpless_param* param = stumpless_get_param_by_index(element, huge);
  EXPECT_NULL(param);
  EXPECT_ERROR_ID_EQ(STUMPLESS_INDEX_OUT_OF_BOUNDS);
}

} // namespace
