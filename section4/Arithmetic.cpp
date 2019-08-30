#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^6
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 100);
auto real_rand = std::uniform_real_distribution<>(0.0, 100.0);

template <typename T>
void add(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      v.first = v.first + v.second;
    }
  }
  return;
}
template <typename T>
void sub(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      v.first = v.first - v.second;
    }
  }
  return;
}
template <typename T>
void mul(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      v.first = v.first * v.second;
    }
  }
  return;
}
template <typename T>
void div(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      v.first = v.first / v.second;
    }
  }
  return;
}

int main() {
  std::vector<std::pair<int, int>> vec_i(vector_num);
  std::vector<std::pair<int64_t, int64_t>> vec_l(vector_num);
  std::vector<std::pair<float, float>> vec_f(vector_num);
  std::vector<std::pair<double, double>> vec_d(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec_i[i] = std::make_pair(int_rand(engine) + 1, int_rand(engine) + 1);
    vec_l[i] = std::make_pair(int_rand(engine) + 1, int_rand(engine) + 1);
    vec_d[i] = std::make_pair(real_rand(engine) + 1, real_rand(engine) + 1);
    vec_f[i] = std::make_pair(static_cast<float>(vec_d[i].first),
                              static_cast<float>(vec_d[i].second));
  }
  std::cout << "---long---" << std::endl;
  add(vec_i);
  sub(vec_i);
  mul(vec_i);
  div(vec_i);

  std::cout << "---long long---" << std::endl;
  add(vec_l);
  sub(vec_l);
  mul(vec_l);
  div(vec_l);

  std::cout << "---float---" << std::endl;
  add(vec_f);
  sub(vec_f);
  mul(vec_f);
  div(vec_f);

  std::cout << "---double---" << std::endl;
  add(vec_d);
  sub(vec_d);
  mul(vec_d);
  div(vec_d);
  return 0;
}

