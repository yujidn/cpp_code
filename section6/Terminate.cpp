#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000;
// 10^1
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 9);

void every_strlen(char *str, int &sum) {
  for (size_t j = 0; j < std::strlen(str); ++j) {
    if (str[j] == '5') {
      sum += 5;
    }
  }
}
void first_strlen(char *str, int &sum) {
  for (size_t j = 0, end = std::strlen(str); j < end; ++j) {
    if (str[j] == '5') {
      sum += 5;
    }
  }
}
void every_end(std::vector<int> &vec, int &sum) {
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    sum += *iter;
  }
}
void first_end(std::vector<int> &vec, int &sum) {
  for (auto iter = vec.begin(), end = vec.end(); iter != end; ++iter) {
    sum += *iter;
  }
}
void for_each(std::vector<int> &vec, int &sum) {
  for (auto &v : vec) {
    sum += v;
  }
}
void std_for_each(std::vector<int> &vec, int &sum) {
  std::for_each(std::begin(vec), std::end(vec), [&](auto &v) { sum += v; });
}

int main(void) {
  char str[vector_num];
  std::vector<int> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    str[i] = static_cast<char>('0' + int_rand(engine));
    vec[i] = int_rand(engine);
  }

  int sum = 0;

  loop_time("every_strlen", loop, every_strlen, str, sum);
  loop_time("first_strlen", loop, first_strlen, str, sum);
  loop_time("every_end", loop, every_end, vec, sum);
  loop_time("first_end", loop, first_end, vec, sum);
  loop_time("for_each", loop, for_each, vec, sum);
  loop_time("std_for_each", loop, std_for_each, vec, sum);

  std::cout << sum << std::endl;
  return 0;
}
