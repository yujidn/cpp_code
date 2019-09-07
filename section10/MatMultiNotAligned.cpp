#include <immintrin.h>
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto real_rand = std::uniform_real_distribution<>(-1.0, 1.0);

void MatMulti(const std::vector<float> &src1, const std::vector<float> &src2,
              std::vector<float> &dst, const size_t &size) {
  FUNC_TIMER;
  size_t rows = size;
  size_t same = size;
  size_t cols = size;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < same; ++j) {
      for (size_t k = 0; k < cols; ++k) {
        dst[cols * i + k] += src1[cols * i + j] * src2[cols * j + k];
      }
    }
  }
}
void MatMultiBySIMD(const std::vector<float> &src1,
                    const std::vector<float> &src2, std::vector<float> &dst,
                    const size_t &size) {
  FUNC_TIMER;
  size_t rows = size;
  size_t same = size;
  size_t cols = size;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < same; ++j) {
      __m256 s1 = _mm256_broadcast_ss(&(src1[cols * i + j]));
      for (size_t k = 0; k < cols; k += 8) {
        __m256 s2 = _mm256_loadu_ps(&(src2[cols * j + k]));
        __m256 d = _mm256_loadu_ps(&(dst[cols * i + k]));
        d = _mm256_fmadd_ps(s1, s2, d);
        _mm256_storeu_ps(&(dst[cols * i + k]), d);
      }
    }
  }
}

void output(const std::vector<float> &dst, const size_t &size) {
  size_t rows = size;
  size_t cols = size;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t k = 0; k < cols; ++k) {
      std::cout << dst[cols * i + k] << ",";
    }
    std::cout << std::endl;
  }
}

int main() {
  const size_t size = 1024;
  std::vector<float> src1(size * size);
  std::vector<float> src2(size * size);
  std::vector<float> result1(size * size);
  std::vector<float> result2(size * size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t k = 0; k < size; ++k) {
      src1[size * i + k] = real_rand(engine);
      src2[size * i + k] = real_rand(engine);
      result1[size * i + k] = 0;
      result2[size * i + k] = 0;
    }
  }

  MatMulti(src1, src2, result1, size);
  MatMultiBySIMD(src1, src2, result2, size);

  return 0;
}
