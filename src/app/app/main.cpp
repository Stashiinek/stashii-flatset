#include <iostream>
#include <librgr/flatset.hpp>

int main(int argc, char **argv) {
  stashii::flatset<int> miau;
  miau.insert(4);
  miau.insert(8);
  miau.insert(2);

  for (int i = 0; i < miau.size(); i++){
    std::cout << miau[i] << "   ";
  }
  std::cout << "\n";
  //stashii::mvec<int> meow;
  return 0;
}
