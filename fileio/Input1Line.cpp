#include <fstream>
#include <iostream>

#include "../timer/timer_class.hpp"

void input_1line(std::ifstream &file, std::string &result) {
  FUNC_TIMER;
  std::string line;
  while (getline(file, line)) {
    result += (line + "\n");
  }
}

int main() {
  std::ifstream f("output1char.txt", std::ios_base::in);
  std::string result;

  input_1line(f, result);
  return 0;
}
