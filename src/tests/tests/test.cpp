#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

TEST(summTest, parsingOne) {
  //EXPECT_EQ(result.at(0).peach, expectedResult.at(0).peach);
  //EXPECT_EQ(result.at(4).peach, expectedResult.at(4).peach);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
