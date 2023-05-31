#include <iostream>
#include <librgr/vector.hpp>

int main(int argc, char **argv) {
  stashii::mvec<int> prim (1);
  prim.push_back(4);
  //prim.at(0) = 5;
  //prim[0] = 6;
  prim.push_back(8);
  prim.push_back(516);
  prim.del_num(0);

  stashii::mvec<int> new_vec;
  new_vec = prim;
  std::cout << new_vec.get_capacity() << "  " << new_vec.get_size() << "\n";
  std::cout << prim.get_capacity() << "  " << prim.get_size() << "\n";
  for (int i = 0; i < new_vec.get_size(); i++){
    std::cout << new_vec[i] << " ";
  }
  prim.clear();
  std::cout << "    " << new_vec.find(7) << "\n";
  return 0;
}
