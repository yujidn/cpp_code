#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(0.0, 5.0);
std::vector<float> randvec(vector_num);

void every_new(double &sum) {
  double *vec = new double[vector_num];
  for (size_t j = 0; j < vector_num; ++j) {
    vec[j] = randvec[j];
    sum += vec[j];
  }
  delete[] vec;
}
void no_new(double &sum, double *vec) {
  for (size_t j = 0; j < vector_num; ++j) {
    vec[j] = randvec[j];
    sum += vec[j];
  }
}

int main(void) {
  double sum = 0;
  for (size_t i = 0; i < vector_num; ++i) {
    randvec[i] = real_rand(engine);
  }

  loop_time("every_new", loop, every_new, sum);
  double *vec = new double[vector_num];
  loop_time("no_new", loop, no_new, sum, vec);
  delete[] vec;

  std::cout << sum << std::endl;
  return 0;
}
