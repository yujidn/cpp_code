#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000 * 1000;

void output_string(std::ofstream &file, const std::string &str) { file << str; }

int main() {
  std::ofstream f("output1LineLF.txt", std::ios_base::out);

  std::vector<std::string> str;
  for (size_t line = 0; line < line_num; ++line) {
    std::stringstream s;
    for (size_t num = 0; num < one_line_char_num; ++num) {
      s << "a";
    }
    s << "\n";
    str.push_back(s.str());
  }

  timer t;
  for (const auto &s : str) {
    output_string(f, s);
  }
  t.print("output_1line_LF");
  return 0;
}
