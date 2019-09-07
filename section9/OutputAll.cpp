#include <fstream>
#include <iostream>
#include <sstream>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000 * 1000;

void output_string(std::ofstream &file, const std::string &str) { file << str; }
int main() {
  std::ofstream f("outputAll.txt", std::ios_base::out);

  std::stringstream s;
  for (size_t line = 0; line < line_num; ++line) {
    for (size_t num = 0; num < one_line_char_num; ++num) {
      s << "a";
    }
    s << std::endl;
  }

  timer t;
  output_string(f, s.str());
  t.print("output_all");
  return 0;
}
