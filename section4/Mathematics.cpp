#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^6
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(0.0, 10.0);

template <typename T>
void sin(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::sin(v.first);
  }
}
template <typename T>
void cos(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::cos(v.first);
  }
}
template <typename T>
void tan(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::tan(v.first);
  }
}
template <typename T>
void asin(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::asin(v.first);
  }
}
template <typename T>
void acos(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::acos(v.first);
  }
}
template <typename T>
void atan(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::atan(v.first);
  }
}

template <typename T>
void exp(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::exp(v.first);
  }
}
template <typename T>
void log(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::log(v.first);
  }
}
template <typename T>
void sqrt(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::sqrt(v.first);
  }
}
template <typename T>
void pow(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.second = std::pow(v.first, v.second);
  }
  return;
}

int main() {
  std::vector<std::pair<float, float>> vec_f(vector_num);
  std::vector<std::pair<double, double>> vec_d(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec_d[i].first = real_rand(engine);
    vec_f[i].first = static_cast<float>(vec_d[i].first);
  }

  std::cout << "---float---" << std::endl;
  loop_time("float sin", loop, (void (*)(decltype(vec_f) &))(sin), vec_f);
  loop_time("float cos", loop, (void (*)(decltype(vec_f) &))(cos), vec_f);
  loop_time("float tan", loop, (void (*)(decltype(vec_f) &))(tan), vec_f);
  loop_time("float asin", loop, (void (*)(decltype(vec_f) &))(asin), vec_f);
  loop_time("float acos", loop, (void (*)(decltype(vec_f) &))(acos), vec_f);
  loop_time("float atan", loop, (void (*)(decltype(vec_f) &))(atan), vec_f);
  loop_time("float exp", loop, (void (*)(decltype(vec_f) &))(exp), vec_f);
  loop_time("float log", loop, (void (*)(decltype(vec_f) &))(log), vec_f);
  loop_time("float sqrt", loop, (void (*)(decltype(vec_f) &))(sqrt), vec_f);
  loop_time("float pow", loop, (void (*)(decltype(vec_f) &))(pow), vec_f);

  std::cout << "---double---" << std::endl;
  loop_time("double sin", loop, (void (*)(decltype(vec_d) &))(sin), vec_d);
  loop_time("double cos", loop, (void (*)(decltype(vec_d) &))(cos), vec_d);
  loop_time("double tan", loop, (void (*)(decltype(vec_d) &))(tan), vec_d);
  loop_time("double asin", loop, (void (*)(decltype(vec_d) &))(asin), vec_d);
  loop_time("double acos", loop, (void (*)(decltype(vec_d) &))(acos), vec_d);
  loop_time("double atan", loop, (void (*)(decltype(vec_d) &))(atan), vec_d);
  loop_time("double exp", loop, (void (*)(decltype(vec_d) &))(exp), vec_d);
  loop_time("double log", loop, (void (*)(decltype(vec_d) &))(log), vec_d);
  loop_time("double sqrt", loop, (void (*)(decltype(vec_d) &))(sqrt), vec_d);
  loop_time("double pow", loop, (void (*)(decltype(vec_d) &))(pow), vec_d);

  return 0;
}

