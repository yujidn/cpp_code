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

std::vector<int> Expansion(std::vector<std::pair<int, int>> &vec) {
  std::vector<int> result(vec.size());
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (size_t j = 0; j < vec.size(); ++j) {
      auto &v = vec[j];
      auto &a = v.first;
      auto &b = v.second;
      result[j] = a * a * a + 3 * a * a * b + 3 * a * b * b + b * b * b;
    }
  }
  return result;
}
std::vector<int> Factorization(std::vector<std::pair<int, int>> &vec) {
  std::vector<int> result(vec.size());
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    for (size_t j = 0; j < vec.size(); ++j) {
      auto &v = vec[j];
      auto &a = v.first;
      auto &b = v.second;
      auto temp = a + b;
      result[j] = temp * temp * temp;
    }
  }
  return result;
}

int main() {
  std::vector<std::pair<int, int>> vec_i(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec_i[i] = std::make_pair(int_rand(engine), int_rand(engine));
  }
  auto vec1 = Expansion(vec_i);
  auto vec2 = Factorization(vec_i);
  std::cout << vec1[0] << "," << vec2[0] << std::endl;

  return 0;
}

