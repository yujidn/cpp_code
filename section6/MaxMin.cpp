#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^9
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(-1000000, 1000000);

int std_min(std::vector<int> &vec) {
  return *std::min_element(vec.begin(), vec.end());
}
int std_max(std::vector<int> &vec) {
  return *std::max_element(vec.begin(), vec.end());
}
int std_min_max(std::vector<int> &vec) {
  auto minmax = std::minmax_element(vec.begin(), vec.end());
  return *minmax.first + *minmax.second;
}

int basic_min(std::vector<int> &vec) {
  int min = INT_MAX;

  min = INT_MAX;
  for (const auto &v : vec) {
    if (min > v) {
      min = v;
    }
  }
  return min;
}
int basic_max(std::vector<int> &vec) {
  int max = INT_MIN;
  max = INT_MIN;
  for (const auto &v : vec) {
    if (v > max) {
      max = v;
    }
  }
  return max;
}
int basic_min_max(std::vector<int> &vec) {
  int min = INT_MAX, max = INT_MIN;

  min = INT_MAX;
  max = INT_MIN;
  for (const auto &v : vec) {
    if (v > max) {
      max = v;
    }
    if (min > v) {
      min = v;
    }
  }
  return min;
}

int main(void) {
  std::vector<int> vec;
  for (size_t j = 0; j < vector_num; ++j) {
    vec.push_back(int_rand(engine));
  }

  int64_t sum = 0;  // 最適化防止
  loop_time("std min", loop, sum, std_min, vec);
  loop_time("std max", loop, sum, std_max, vec);
  loop_time("std minmax", loop, sum, std_min_max, vec);

  loop_time("basic min", loop, sum, basic_min, vec);
  loop_time("basic max", loop, sum, basic_max, vec);
  loop_time("basic minmax", loop, sum, basic_min_max, vec);
  std::cout << sum << std::endl;
  return 0;
}
