#include <immintrin.h>
#include <iostream>

const size_t vector_num = 1024;

void CopyBySIMD(const float *src, float *dst) {
  for (size_t i = 0; i < vector_num; i += 8) {
    __m256 load = _mm256_load_ps(&src[i]);
    _mm256_store_ps(&dst[i], load);
  }
}

void CopyBySIMDNotAligned(const float *src, float *dst) {
  for (size_t i = 0; i < vector_num; i += 8) {
    __m256 load = _mm256_loadu_ps(&src[i + 1]);
    _mm256_storeu_ps(&dst[i + 1], load);
  }
}

void CopyBySIMDSegv(const float *src, float *dst) {
  for (size_t i = 0; i < vector_num; i += 8) {
    __m256 load = _mm256_load_ps(&src[i + 1]);
    _mm256_store_ps(&dst[i + 1], load);
  }
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
  CopyBySIMD(src, dst);
  std::cout << dst[0] << std::endl;

  std::cout << "アンアライメントアドレスへのloadu/storeu" << std::endl;
  CopyBySIMDNotAligned(src, dst);
  std::cout << dst[0] << std::endl;

  std::cout << "アンアライメントアドレスへのload/store" << std::endl;
  CopyBySIMDSegv(src, dst);
  std::cout << dst[1] << std::endl;
  return 0;
}
