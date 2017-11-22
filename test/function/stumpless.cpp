#include <gtest/gtest.h>
#include <stumpless.h>
#include <stumpless/error.h>

TEST(StumplessTest, RawString){
  EXPECT_EQ(0, stumpless("testing"));
  EXPECT_EQ(NULL, stumpless_get_error());
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
