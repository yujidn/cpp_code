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
auto int_rand = std::uniform_int_distribution<>(1, 1 << 30);

template <typename T>
void mod(std::vector<T> &vec) {
  for (auto &v : vec) {
    v.first = v.first % v.second;
  }
  return;
}
template <typename T>
void mod2power(std::vector<T> &vec) {
  for (auto &v : vec) {
    v.first = v.first & (v.second - 1);
  }
  return;
}

int main() {
  std::vector<std::pair<int, int>> vec_i(vector_num);
  std::vector<std::pair<int, int>> vec_i2power(vector_num);
  std::vector<std::pair<int64_t, int64_t>> vec_l(vector_num);
  std::vector<std::pair<int64_t, int64_t>> vec_l2power(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec_i[i] = std::make_pair(int_rand(engine), int_rand(engine));
    vec_l[i] = std::make_pair(int_rand(engine), int_rand(engine));
    vec_i2power[i] =
        std::make_pair(int_rand(engine), 1 << (int_rand(engine) % 31));
    vec_l2power[i] =
        std::make_pair(int_rand(engine), 1 << (int_rand(engine) % 31));
  }
  std::cout << "---long---" << std::endl;
  loop_time("long mod", loop, (void (*)(decltype(vec_i) &))(mod), vec_i);
  loop_time("long mod2power", loop,
            (void (*)(decltype(vec_i2power) &))(mod2power), vec_i2power);

  std::cout << "---long long---" << std::endl;
  loop_time("long long mod", loop, (void (*)(decltype(vec_l) &))(mod), vec_l);
  loop_time("long long mod2power", loop,
            (void (*)(decltype(vec_l2power) &))(mod2power), vec_l2power);

  return 0;
}

