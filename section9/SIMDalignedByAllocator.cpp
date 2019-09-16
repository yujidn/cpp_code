#include <immintrin.h>
#include <iostream>
#include <vector>

#include "aligned_allocator.hpp"

const size_t vector_num = 1024 * 1024;

void copy_by_simd(const std::vector<float, aligned_allocator<float>> &src,
                  std::vector<float, aligned_allocator<float>> &dst) {
  if (src.size() != dst.size()) {
    return;
  }
  for (size_t i = 0, end = src.size(); i < end; i += 8) {
    _mm256_store_ps(&dst[i], _mm256_load_ps(&src[i]));
  }
}

int main() {
  std::vector<float, aligned_allocator<float>> src(vector_num);
  for (size_t i = 0, e = src.size(); i < e; ++i) {
    src[i] = i;
  }
  std::vector<float, aligned_allocator<float>> dst(vector_num);
  std::cout << std::hex << "src:" << reinterpret_cast<long long>(&src[0])
            << "\n"
            << "dst:" << reinterpret_cast<long long>(&dst[0]) << std::endl;

  copy_by_simd(src, dst);

  std::cout << dst[0] << std::endl;

  return 0;
}
