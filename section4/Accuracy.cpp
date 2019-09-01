#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

const uint64_t N = 1000;
// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(-1.0, 1.0);

template <uint64_t N>
struct constexpr_calced_asin {
 public:
  double calced[2 * N + 1];
  constexpr constexpr_calced_asin() : calced() {
    for (int64_t i = 0; i <= 2 * N; ++i) {
      double temp = (static_cast<double>(i) - N) / N;
      calced[i] = std::asin(temp);
    }
  }
  const double get_asin(const double &t) const {
    return calced[static_cast<uint64_t>(N * t + N)];
  }
};

double kodo2kakudo(double t) { return t * 180 / M_PI; }

double asin(const std::vector<double> &vec) {
  FUNC_TIMER;
  double sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    for (const auto &v : vec) {
      sum += std::asin(v);
    }
  }
  return sum;
}

double constexpr_asin(const std::vector<double> &vec) {
  FUNC_TIMER;
  constexpr auto calced_asin = constexpr_calced_asin<N>();
  double sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    for (const auto &v : vec) {
      sum += calced_asin.get_asin(v);
    }
  }
  return sum;
}

int main() {
  constexpr auto calced_asin = constexpr_calced_asin<N>();
  std::vector<double> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec[i] = real_rand(engine);
  }

  double sum = 0;
  for (auto &v : vec) {
    sum += std::abs(kodo2kakudo(std::asin(v)) -
                    kodo2kakudo(calced_asin.get_asin(v)));
  }
  std::cout << sum / vec.size() << std::endl;

  loop_time(
      "asin", loop,
      [](const std::vector<double> &vec) {
        FUNC_TIMER;
        double sum = 0;
        for (const auto &v : vec) {
          sum += std::asin(v);
        }
      },
      vec);

  sum += asin(vec);
  sum += constexpr_asin(vec);
  std::cout << sum << std::endl;
  return 0;
}

