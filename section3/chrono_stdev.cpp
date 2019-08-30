#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

const uint64_t count = 1000000;

int main() {
  std::vector<uint64_t> vec;
  vec.reserve(count);

  for (uint64_t i = 0; i < count; ++i) {
    auto s = std::chrono::system_clock::now();
    std::chrono::system_clock::now();
    auto e = std::chrono::system_clock::now();
    vec.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count());
  }

  uint64_t min = 100000, max = 0, ave = 0, aveave = 0;
  for (const auto &i : vec) {
    if (min > i) min = i;
    if (max < i) max = i;
    ave += i;
    aveave += i * i;
  }

  ave = ave / count;
  aveave = aveave / count;

  std::cout << "min  :" << min << std::endl;
  std::cout << "max  :" << max << std::endl;
  std::cout << "ave  :" << ave << std::endl;
  std::cout << "stdev:" << std::sqrt(aveave - ave) << std::endl;

  return 0;
}
