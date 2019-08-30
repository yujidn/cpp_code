#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"
// 10^9
const uint64_t vector_num = 1000 * 1000 * 1000;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 100);

int sequence_access(const std::vector<int> &vec,
                    const std::vector<int> &access) {
  FUNC_TIMER;
  int sum = 0;

  for (uint64_t j = 0; j < vector_num; ++j) {
    sum += vec[access[j]];
  }
  return sum;
}

int random_access(const std::vector<int> &vec, std::vector<int> &access) {
  std::shuffle(access.begin(), access.end(), engine);
  FUNC_TIMER;
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

  sum += sequence_access(vec, access);
  sum += random_access(vec, access);

  std::cout << sum << std::endl;
  return 0;
}
