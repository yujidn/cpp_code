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
void add(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first + v.second;
  }
  return;
}

template <typename T>
void sub(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first - v.second;
  }
  return;
}
template <typename T>
void mul(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first * v.second;
  }
  return;
}
template <typename T>
void div(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first / v.second;
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
  loop_time("long add", loop, (void (*)(decltype(vec_i) &))(add), vec_i);
  loop_time("long sub", loop, (void (*)(decltype(vec_i) &))(sub), vec_i);
  loop_time("long mul", loop, (void (*)(decltype(vec_i) &))(mul), vec_i);
  loop_time("long div", loop, (void (*)(decltype(vec_i) &))(div), vec_i);

  std::cout << "---long long---" << std::endl;
  loop_time("long long add", loop, (void (*)(decltype(vec_l) &))(add), vec_l);
  loop_time("long long sub", loop, (void (*)(decltype(vec_l) &))(sub), vec_l);
  loop_time("long long mul", loop, (void (*)(decltype(vec_l) &))(mul), vec_l);
  loop_time("long long div", loop, (void (*)(decltype(vec_l) &))(div), vec_l);

  std::cout << "---float---" << std::endl;
  loop_time("float add", loop, (void (*)(decltype(vec_f) &))(add), vec_f);
  loop_time("float sub", loop, (void (*)(decltype(vec_f) &))(sub), vec_f);
  loop_time("float mul", loop, (void (*)(decltype(vec_f) &))(mul), vec_f);
  loop_time("float div", loop, (void (*)(decltype(vec_f) &))(div), vec_f);

  std::cout << "---double---" << std::endl;
  loop_time("double add", loop, (void (*)(decltype(vec_d) &))(add), vec_d);
  loop_time("double sub", loop, (void (*)(decltype(vec_d) &))(sub), vec_d);
  loop_time("double mul", loop, (void (*)(decltype(vec_d) &))(mul), vec_d);
  loop_time("double div", loop, (void (*)(decltype(vec_d) &))(div), vec_d);
  return 0;
}

