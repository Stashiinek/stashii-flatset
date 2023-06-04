#include <iostream>
#include <librgr/flatset.hpp>

int main(int argc, char **argv) {
  stashii::mvec<int> meow;
  meow.push_back(4);
  meow.push_back(8);
  meow.push_back(2);
  meow.push_back(7);
  meow.push_back(6);
  meow.push_back(12);
  stashii::flatset<int> miau (meow);
  auto b = miau.begin();
  stashii::flatset<int>::flatIterator miauiterator (miau.last());
  std::cout << miau[0] << "\n";
  stashii::flatset<int>::flatIterator miauend (miau.begin());

  for (; miauiterator >= miauend; --miauiterator){
    std::cout << *miauiterator << "   ";
  }
  std::cout << "\n" << miau.lower_bound(1) << " " << miau.upper_bound(1);
  std::cout << "\n";
  std::cout << *miau.find(5) << "\n";
  miau.clear();

  return 0;
}
