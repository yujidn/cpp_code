#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^9
const uint64_t vector_num = 1000 * 1000 * 1000;
// 10^3
const size_t loop = 1;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(-1000000, 1000000);

template <typename T>
T std_min(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    vec[i] = INT_MAX - *std::min_element(vec.begin(), vec.end());
  }
  return *std::min_element(vec.begin(), vec.end());
}
template <typename T>
T std_max(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    vec[i] = INT_MAX - *std::max_element(vec.begin(), vec.end());
  }
  return *std::max_element(vec.begin(), vec.end());
}
template <typename T>
T std_min_max(std::vector<T> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    auto result = std::minmax_element(vec.begin(), vec.end());
    vec[i] = INT_MAX - *result.first + *result.second;
  }
  return *std::minmax_element(vec.begin(), vec.end()).first;
}

template <typename T>
T basic_min(std::vector<T> &vec) {
  FUNC_TIMER;
  T min = INT_MAX;

  for (size_t i = 0; i < loop; ++i) {
    min = INT_MAX;
    for (const auto &v : vec) {
      if (min > v) {
        min = v;
      }
    }
    vec[i] = INT_MAX - min;
  }
  return min;
}
template <typename T>
T basic_max(std::vector<T> &vec) {
  FUNC_TIMER;
  T max = INT_MIN;
  for (size_t i = 0; i < loop; ++i) {
    max = INT_MIN;
    for (const auto &v : vec) {
      if (v > max) {
        max = v;
      }
    }
    vec[i] = INT_MAX - max;
  }
  return max;
}
template <typename T>
T basic_min_max(std::vector<T> &vec) {
  FUNC_TIMER;
  T min = INT_MAX, max = INT_MIN;

  for (size_t i = 0; i < loop; ++i) {
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
    vec[i] = INT_MAX - min + max;
  }
  return min;
}

template <typename T>
T no_if_min(std::vector<T> &vec) {
  FUNC_TIMER;
  T min = INT_MAX;
  for (size_t i = 0; i < loop; ++i) {
    min = INT_MAX;
    for (const auto &v : vec) {
      auto tmin = ((min - v) >> (sizeof(T) * 8 - 1));
      min = (min & tmin) | (v & (tmin ^ (-1)));
    }
    vec[i] = INT_MAX - min;
  }
  return min;
}
template <typename T>
T no_if_max(std::vector<T> &vec) {
  FUNC_TIMER;
  T max = INT_MIN;
  for (size_t i = 0; i < loop; ++i) {
    max = INT_MIN;
    for (const auto &v : vec) {
      auto tmax = ((max - v) >> (sizeof(T) * 8 - 1));
      max = (max & (tmax ^ (-1)) | (v & tmax));
    }
    vec[i] = INT_MAX - max;
  }
  return max;
}
template <typename T>
T no_if_min_max(std::vector<T> &vec) {
  FUNC_TIMER;
  T min = INT_MAX, max = INT_MIN;
  for (size_t i = 0; i < loop; ++i) {
    min = INT_MAX;
    max = INT_MIN;
    for (const auto &v : vec) {
      auto tmax = ((max - v) >> (sizeof(T) * 8 - 1));
      auto tmin = ((min - v) >> (sizeof(T) * 8 - 1));
      max = (max & (tmax ^ (-1)) | (v & tmax));
      min = (min & tmin) | (v & (tmin ^ (-1)));
    }
    vec[i] = INT_MAX - min + max;
  }
  return min;
}

int main(void) {
  std::vector<int> vec;
  for (size_t j = 0; j < vector_num; ++j) {
    vec.push_back(int_rand(engine));
  }

  double sum = 0;  // 最適化防止
  sum += std_min(vec);
  sum += std_max(vec);
  sum += std_min_max(vec);
  sum += basic_min(vec);
  sum += basic_max(vec);
  sum += basic_min_max(vec);
  sum += no_if_min(vec);
  sum += no_if_max(vec);
  sum += no_if_min_max(vec);
  std::cout << sum << std::endl;
  return 0;
}

