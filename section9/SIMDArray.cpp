#include <immintrin.h>
#include <iostream>

const size_t vector_num = 1024;

void copy_by_simd(const float *src, float *dst) {
  __m256 load = _mm256_load_ps(&src[0]);
  _mm256_store_ps(&dst[0], load);
}

void copy_by_simd_not_aligned(const float *src, float *dst) {
  __m256 load = _mm256_loadu_ps(&src[1]);
  _mm256_storeu_ps(&dst[1], load);
}

void copy_by_simd_segv(const float *src, float *dst) {
  __m256 load = _mm256_load_ps(&src[1]);
  _mm256_store_ps(&dst[1], load);
}

int main() {
  alignas(32) float src[vector_num];
  for (size_t i = 0; i < vector_num; ++i) {
    src[i] = i;
  }
  alignas(32) float dst[vector_num];
  std::cout << std::hex << "src address : 0x"
            << reinterpret_cast<long long>(&src[0]) << "\n"
            << "dst address : 0x" << reinterpret_cast<long long>(&dst[0])
            << std::endl;
  std::cout << "アライメントアドレスへのload/store" << std::endl;
  copy_by_simd(src, dst);
  std::cout << dst[0] << std::endl;
  std::cout << "アンアライメントアドレスへのloadu/storeu" << std::endl;
  copy_by_simd_not_aligned(src, dst);
  std::cout << dst[1] << std::endl;
  std::cout << "アンアライメントアドレスへのload/store" << std::endl;
  copy_by_simd_segv(src, dst);
  std::cout << dst[1] << std::endl;

  return 0;
}
