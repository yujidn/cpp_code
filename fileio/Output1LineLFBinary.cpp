#include <fstream>
#include <iostream>
#include <sstream>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000 * 1000;

int main() {
  std::ofstream f("outputBinary.bin",
                  std::ios_base::out | std::ios_base::binary);

  timer t;
  for (size_t line = 0; line < line_num; ++line) {
    std::stringstream s;
    for (size_t num = 0; num < one_line_char_num; ++num) {
      s << "\n";
    }
    const char *c = s.str().c_str();
    f.write(c, sizeof(c));
  }
  t.print("output_1line_LF_Binary");
  return 0;
}
