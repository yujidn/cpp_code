#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^9
const uint64_t vector_num = 1000 * 1000 * 1000;
// 10^1
const size_t loop = 1;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(0.0, 5.0);

void rotate_repeat(const double &theta,
                   std::vector<std::pair<double, double>> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      auto &x = v.first;
      auto &y = v.second;

      auto tx = std::cos(theta) * x - std::sin(theta) * y;
      auto ty = std::sin(theta) * x + std::cos(theta) * y;
      x = tx;
      y = ty;
    }
  }
}

void rotate(const double &theta, std::vector<std::pair<double, double>> &vec) {
  FUNC_TIMER;
  const auto sin = std::sin(theta);
  const auto cos = std::cos(theta);

  for (size_t i = 0; i < loop; ++i) {
    for (auto &v : vec) {
      auto &x = v.first;
      auto &y = v.second;
      auto tx = cos * x - sin * y;
      auto ty = sin * x + cos * y;
      x = tx;
      y = ty;
    }
  }
}
int main(void) {
  std::vector<std::pair<double, double>> vec;
  for (size_t i = 0; i < vector_num; ++i) {
    vec.push_back(std::make_pair(real_rand(engine), real_rand(engine)));
  }

  // 45 degree
  const double theta = 3.14 / 4;

  rotate_repeat(theta, vec);

  double sum = 0.0;  // 最適化で消えるの防止
  for (auto &v : vec) {
    sum += v.first + v.second;
  }

  rotate(theta, vec);

  for (auto &v : vec) {  // 最適化で消えるの防止
    sum += v.first + v.second;
  }

  std::cout << sum << std::endl;
}
