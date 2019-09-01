#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^6
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 10);

void plus_one(uint64_t &val) { val += 1; }
void plus_one(std::vector<uint64_t> &vec) {
  for (auto &v : vec) {
    v += 1;
  }
}

void plus_one_by_func(std::vector<uint64_t> &vec) {
  for (auto &v : vec) {
    plus_one(v);
  }
}

void plus_one_by_loop(std::vector<uint64_t> &vec) { plus_one(vec); }

int main(void) {
  std::vector<uint64_t> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec[i] = int_rand(engine);
  }

  loop_time("plus one by func", loop, plus_one_by_func, vec);
  loop_time("plus one by loop", loop, plus_one_by_loop, vec);

  size_t sum = 0;
  for (auto &v : vec) {
    sum += v;
  }
  std::cout << sum << std::endl;
}

