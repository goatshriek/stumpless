#include <stddef.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/error.h>

namespace {

  class BufferTargetTest : public ::testing::Test {
    protected:
      char buffer[100];
      struct stumpless_target *target;

      virtual void SetUp(){
        target = stumpless_open_buffer_target("buffer target testing", buffer, 100, 0, 0);
      }

      virtual void TearDown(){
        stumpless_close_buffer_target(target);
      }
  };

  // todo need to move this to a different test case without the fixture
  TEST_F(BufferTargetTest, NormalOpenTarget){
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target("normal target", buffer, 100, 0, 0);
    ASSERT_TRUE(target != NULL);

    EXPECT_EQ(target, stumpless_get_current_target());

    stumpless_close_buffer_target(target);
  }

  TEST_F(BufferTargetTest, Basic){
    ASSERT_TRUE(stumpless_get_current_target() != NULL);

    EXPECT_EQ(0, stumpless("testing 1"));
    EXPECT_EQ(NULL, stumpless_get_error());
  }
  
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
