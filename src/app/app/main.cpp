#include <iostream>
#include <librgr/flatset.hpp>

int main(int argc, char **argv) {
  stashii::flatset<int> miau;
  
  miau.insert(4);
  miau.insert(8);
  miau.insert(2);
  miau.insert(7);
  miau.insert(6);
  miau.insert(12);

  for (int i = 0; i < miau.size(); i++){
    std::cout << miau[i] << "   ";
  }
  std::cout << "\n" << miau.lower_bound(5) << " " << miau.upper_bound(5);
  std::cout << "\n";


  //std::cout << miau.diff(4, 3) << "   " << miau.diff(3, 4) << "\n";
  
  //stashii::mvec<int> meow;
  return 0;
}
