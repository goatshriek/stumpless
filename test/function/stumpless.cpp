#include <gtest/gtest.h>

extern "C" int stumpless(const char *message);

TEST(StumplessTest, RawString){
  EXPECT_EQ(0, stumpless("testing"));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
