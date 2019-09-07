#include <fstream>
#include <iostream>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000 * 1000;

int main() {
  std::ofstream f("output1char.txt", std::ios_base::out);

  timer t;
  for (size_t line = 0; line < line_num; ++line) {
    for (size_t num = 0; num < one_line_char_num; ++num) {
      f << "a";
    }
    f << "\n";
  }
  t.print("output_1char");
  return 0;
}
