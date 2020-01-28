#include <gtest/gtest.h>

#include "../src/hello_posd.h"

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(HelloTest, helloPosd)
{
  ASSERT_EQ("hello, posd!", helloPosd());
}
