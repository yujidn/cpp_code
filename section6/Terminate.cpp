#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^0
const size_t loop = 1;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 9);

void every_strlen(char *str, int &sum) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (size_t j = 0; j < std::strlen(str); ++j) {
      if (str[j] == '5') {
        sum += 5;
      }
    }
  }
}

void first_strlen(char *str, int &sum) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (size_t j = 0, end = std::strlen(str); j < end; ++j) {
      if (str[j] == '5') {
        sum += 5;
      }
    }
  }
}

int main(void) {
  char str[vector_num];
  for (size_t i = 0; i < vector_num; ++i) {
    str[i] = static_cast<char>('0' + int_rand(engine));
  }

  int sum = 0;

  every_strlen(str, sum);
  first_strlen(str, sum);

  std::cout << sum << std::endl;
}
