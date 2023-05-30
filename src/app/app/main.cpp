#include <iostream>
#include <librgr/vector.hpp>

int main(int argc, char **argv) {
  kwangya::miauVector<int> prim (1);
  prim.push_back(4);
  //prim.at(0) = 5;
  //prim[0] = 6;
  //prim.push_back(8);
  //prim.push_back(516);
  //prim.pop_back();
  for (int i = 0; i < prim.get_size(); i++){
    std::cout << prim[i] << " ";
  }
  std::cout << "\n";
  return 0;
}
