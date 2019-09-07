#include <fstream>
#include <iostream>

#include "../timer/timer_class.hpp"

template <typename T>
void input_binary(std::ifstream &file, std::vector<T> &vec) {
  FUNC_TIMER;
  file.seekg(0, file.end);
  int size = file.tellg() / sizeof(T);
  file.seekg(0, file.beg);

  std::cout << size << std::endl;
  vec.resize(size);
  file.read(reinterpret_cast<char *>(&vec[0]), size);
}

int main() {
  std::ifstream f("outputBinary.bin",
                  std::ios_base::in | std::ios_base::binary);
  std::string result;

  std::vector<int> vec;

  input_binary(f, vec);

  return 0;
}
