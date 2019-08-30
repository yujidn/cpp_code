#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^9
const uint64_t vector_num = 1000 * 1000 * 1000;
// 10^6
const size_t loop = 1;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 9);

int no_reference_loop(const std::vector<int> &vec) {
  int64_t sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    for (auto v : vec) {
      sum += v;
    }
  }
  return sum;
}

int reference_loop(const std::vector<int> &vec) {
  int64_t sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      sum += v;
    }
  }
  return sum;
}
int main(void) {
  std::vector<int> vec;
  for (size_t i = 0; i < vector_num; ++i) {
    vec.push_back(int_rand(engine));
  }

  int64_t sum = 0;
  sum += no_reference_loop(vec);
  sum += reference_loop(vec);

  std::cout << sum << std::endl;
}
