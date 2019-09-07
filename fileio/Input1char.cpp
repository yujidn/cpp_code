#include <fstream>
#include <iostream>
#include <sstream>

#include "../timer/timer_class.hpp"

void input_1char(std::ifstream &file, std::string &result) {
  FUNC_TIMER;
  std::stringstream s;
  s << file.rdbuf();
  result = std::move(s.str());
}
int main() {
  std::ifstream f("output1char.txt", std::ios_base::in);
  std::string result;

  input_1char(f, result);
  return 0;
}
