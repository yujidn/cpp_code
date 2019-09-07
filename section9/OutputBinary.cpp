#include <fstream>
#include <iostream>

#include "../timer/timer_class.hpp"

const size_t one_line_char_num = 100;
const size_t line_num = 1000 * 1000;

template <typename T>
void output_binary(std::ofstream &file, T *val, const size_t size) {
  FUNC_TIMER;
  file.write(reinterpret_cast<char *>(val), size);
}

int main() {
  std::ofstream f("outputBinary.bin",
                  std::ios_base::out | std::ios_base::binary);

  std::vector<int> vec;
  for (size_t line = 0; line < line_num; ++line) {
    for (size_t num = 0; num < one_line_char_num; ++num) {
      vec.push_back((line + 1) * num);
    }
  }
  output_binary(f, &vec[0], sizeof(int) * vec.size());
  return 0;
}
