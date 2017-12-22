#include <stddef.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <stumpless/error.h>

namespace {

  class StumplessTest : public ::testing::Test {};

  TEST(StumplessTest, RawString){
    EXPECT_EQ(0, stumpless("testing 1"));
    EXPECT_EQ(0, stumpless("testing 2"));
    EXPECT_EQ(0, stumpless("testing 3"));
    EXPECT_EQ(NULL, stumpless_get_error());
  }
  
  TEST(GetStumplessVersionTest, Function){
    struct stumpless_version *version;
  
    version = get_stumpless_version();
  
    ASSERT_TRUE(version != NULL);
    ASSERT_TRUE(version->major >= 0);
    ASSERT_TRUE(version->minor >= 0);
    ASSERT_TRUE(version->patch >= 0);
  }
  
  TEST(GetStumplessVersionTest, Defines){
    #ifndef STUMPLESS_MAJOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_MINOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_PATCH_VERSION
      FAIL();
    #endif
  }

}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
