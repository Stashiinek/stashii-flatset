#include <iostream>
#include <librgr/flatset.hpp>

int main(int argc, char **argv) {
  stashii::flatset<int> miau;
  miau.insert(7);
  miau.insert(6);
  miau.insert(4);
  //std::cout << "meowing...\n";
  miau.remove(6);
  miau.insert(5);
  //miau.remove(4);
  stashii::flatset<int>::flatIterator miauiterator (miau.last());
  stashii::flatset<int>::flatIterator miauend (miau.begin());

  for (; miauiterator >= miauend; miauiterator--){
    std::cout << *miauiterator << "   ";
  }
  std::cout << "\n" << miau.lower_bound(1) << " " << miau.upper_bound(1) << "\n";
  std::cout << "Find 5: " << miau.exist(5) << ", find 6: " << miau.exist(6) << "\n";
  std::cout << "\n";
  std::cout << *miau.find(5) << "\n";
  miau.clear();

  return 0;
}
