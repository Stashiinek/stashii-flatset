#include <iostream>
#include <librgr/flatset.hpp>

using namespace stashii;

int main(int argc, char **argv) {
  //EXPECT_EQ(check, true);
  stashii::mvec<int> meow (3);
  meow.push_back(7);
  meow.push_back(7);
  meow.push_back(4);
  meow.push_back(6);
  meow.push_back(5);
  stashii::flatset<int> miau = meow;
  miau.insert(4);
  miau.remove(6);
  miau.insert(5);
  miau.remove(3);

  stashii::flatset<int>::flatIterator miauiterator (miau.last());
  miau.insert(10);
  //miau.clear();
  miauiterator++;
  stashii::flatset<int>::flatIterator miauend (miau.begin());

  for (; miauiterator >= miauend; --miauiterator){
    std::cout << *miauiterator << "   ";
  }
  std::cout << "\n" << miau.lower_bound(1) << " " << miau.upper_bound(1) << "\n";
  std::cout << "Find 5: " << miau.exist(5) << ", find 6: " << miau.exist(6) << "\n";
  std::cout << "\n";
  std::cout << *miau.find(5) << "\n";
  miau.clear();

  return 0;
}
