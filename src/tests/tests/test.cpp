#include <gtest/gtest.h>
#include <iostream>

#include <librgr/flatset.hpp>

using namespace stashii;

TEST(fltst, operators1) {
  flatset<int> testing (4);
  mvec<int> vect (5);
  vect.push_back(3);
  testing = vect;

  EXPECT_EQ(testing.size(), vect.get_size());

  EXPECT_EQ(vect[0], testing[1]);
  EXPECT_EQ(vect[1], testing[0]);
}

TEST(fltst, operators2){
  flatset<int> set = {2, 5, 1, 7, 6, 3, 2};

  EXPECT_EQ(set[0], 1);
  EXPECT_EQ(set[3], 5);
}

TEST(fltst, ex1st){
  flatset<int> set = {2, 5, 1, 7, 6, 3, 2};

  bool n = set.exist(4);
  bool e = set.exist(7);
  EXPECT_EQ(n, false);
  EXPECT_EQ(e, true);
}

TEST(fltst, ind){
  flatset<float> set = {3.5, 7, 631, 4.72, 5};

  auto frst = set.index(4.72);
  auto n = set.index(6);
  size_t s = set.size();

  EXPECT_EQ(frst, 1);
  EXPECT_EQ(n, s);
}

TEST(fltst, emp7y){
  flatset<int> miau;
  bool em = miau.empty();
  EXPECT_EQ(true, em);

  miau = {2, 5, 1, 7, 6, 3, 2};
  em = miau.empty();
  EXPECT_EQ(false, em);

  miau.clear();
  em = miau.empty();
  EXPECT_EQ(true, em);
}

TEST(fltst, insrtrm){
  flatset<float, std::greater<>> miau = {4, 6, 5};
  miau.insert(3);
  bool check = miau.exist(3);
  EXPECT_EQ(check, true);

  miau.insert(2);
  miau.remove(4);
  check = miau.exist(4);
  EXPECT_EQ(check, false);
}

TEST(fltst, lwrupr){
  flatset<int> miau = {2, 5, 1, 7, 6, 3, 2};
  flatset<int, std::greater<>> meow = {2, 5, 1, 7, 6, 3, 2};

  int lower = miau.lower_bound(4);
  int upper = miau.upper_bound(4);
  EXPECT_EQ(lower, 3);
  EXPECT_EQ(upper, 5);

  lower = meow.lower_bound(7);
  upper = meow.upper_bound(7);
  EXPECT_EQ(lower, 6);
  EXPECT_EQ(upper, 7);

  lower = meow.lower_bound(1);
  upper = meow.upper_bound(1);
  EXPECT_EQ(lower, 1);
  EXPECT_EQ(upper, 2);

  lower = meow.lower_bound(3);
  upper = meow.upper_bound(3);
  EXPECT_EQ(lower, 2);
  EXPECT_EQ(upper, 5);
}

TEST(fltst, iter1){
  flatset<int, std::greater<>> meow = {2, 5, 1, 7, 6, 3, 2};
  flatset<int, std::greater<>>::flatIterator miau = meow.begin();

  ++miau;
  auto m = *miau;
  EXPECT_EQ(m, meow[1]);
  
  miau++;
  m = *miau;
  EXPECT_EQ(m, meow[2]);

  miau--;
  m = *miau;
  EXPECT_EQ(m, meow[1]);
}

TEST(fltst, iter2){
  flatset<float> m = {3.4, 2, 4.5};
  flatset<float>::flatIterator m1 = m.begin();
  flatset<float>::flatIterator m2 = m.last();

  --m2;
  m1++;
  bool d = (m1 == m2);
  EXPECT_EQ(d, true);
}

TEST(fltst, iter3){
  flatset<float> m = {3.4, 2, 4.5};
  flatset<float>::flatIterator m1 = m.find(3);
  flatset<float>::flatIterator m2 = m.end();

  bool d = (m1 == m2);
  EXPECT_EQ(d, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
