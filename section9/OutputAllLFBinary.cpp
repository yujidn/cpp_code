#include <fstream>
#include <iostream>
#include <sstream>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000;

int main() {
  std::ofstream f("outputAllLFBinary.bin",
                  std::ios_base::out | std::ios_base::binary);

  std::stringstream s;
  for (size_t line = 0; line < line_num; ++line) {
    for (size_t num = 0; num < one_line_char_num; ++num) {
      s << "a";
    }
    s << "\n";
  }

  timer t;
  const char *c = s.str().c_str();
  std::cout << sizeof(c) << std::endl;
  f.write(c, sizeof(c));
  t.print("output_all_LF_Binary");
  return 0;
}
