#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"
// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 100);

int sequence_access(const std::vector<int> &vec,
                    const std::vector<int> &access) {
  int sum = 0;

  for (uint64_t j = 0; j < vector_num; ++j) {
    sum += vec[access[j]];
  }
  return sum;
}

int main() {
  std::vector<int> vec(vector_num);
  std::vector<int> access(vector_num);
  for (uint64_t i = 0; i < vector_num; ++i) {
    vec[i] = int_rand(engine);
    access[i] = i;
  }
  int sum = 0;

  loop_time("sequence access", loop, sum, sequence_access, vec, access);
  std::shuffle(access.begin(), access.end(), engine);
  loop_time("random access", loop, sum, sequence_access, vec, access);

  std::cout << sum << std::endl;
  return 0;
}
