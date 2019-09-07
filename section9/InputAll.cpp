#include <fstream>
#include <iostream>

#include "../timer/timer_class.hpp"

void input_all(std::ifstream &file, std::string &result) {
  FUNC_TIMER;
  file.seekg(0, file.end);
  int size = file.tellg();
  file.seekg(0, file.beg);

  result.resize(size);
  file.read(&result[0], size);
}

int main() {
  std::ifstream f("output1char.txt", std::ios_base::in);
  std::string result;

  input_all(f, result);

  return 0;
}
