#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(0.0, 100.0);

double variance(const std::vector<double> &vec) {
  double sum_for_ave = 0.0;
  for (const auto &v : vec) {
    sum_for_ave += v;
  }
  auto average = sum_for_ave / vec.size();

  double sum_for_var = 0.0;
  for (const auto &v : vec) {
    auto temp = v - average;
    sum_for_var += temp * temp;
  }

  return sum_for_var / vec.size();
}

double expansion_variance(const std::vector<double> &vec) {
  double sum = 0.0;
  double sumsum = 0.0;
  for (const auto &v : vec) {
    sum += v;
    sumsum += v * v;
  }
  auto average = sum / vec.size();

  return sumsum / vec.size() - average * average;
}

int main() {
  std::vector<double> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec[i] = real_rand(engine);
  }
  double sum = 0.0;
  loop_time("variance", loop, sum, variance, vec);
  loop_time("expansion_variance", loop, sum, expansion_variance, vec);

  return 0;
}

