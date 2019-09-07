#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(0.0, 5.0);

void rotate_repeat(const double &theta,
                   std::vector<std::pair<double, double>> &vec) {
  for (auto &v : vec) {
    auto &x = v.first;
    auto &y = v.second;

    auto tx = std::cos(theta) * x - std::sin(theta) * y;
    auto ty = std::sin(theta) * x + std::cos(theta) * y;
    x = tx;
    y = ty;
  }
}

void rotate(const double sin, const double cos,
            std::vector<std::pair<double, double>> &vec) {
  for (auto &v : vec) {
    auto &x = v.first;
    auto &y = v.second;
    auto tx = cos * x - sin * y;
    auto ty = sin * x + cos * y;
    x = tx;
    y = ty;
  }
}

int main(void) {
  std::vector<std::pair<double, double>> vec;
  double sum = 0.0;
  for (size_t i = 0; i < vector_num; ++i) {
    sum += real_rand(engine);
    vec.push_back(std::make_pair(real_rand(engine), real_rand(engine)));
  }

  const double theta = sum;
  const auto sin = std::sin(theta);
  const auto cos = std::cos(theta);

  loop_time("rotate repeat", loop, rotate_repeat, theta, vec);
  loop_time("rotate", loop, rotate, sin, cos, vec);

  return 0;
}
