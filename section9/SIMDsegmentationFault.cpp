#include <immintrin.h>
#include <iostream>
#include <vector>

const size_t vector_num = 1024 * 1024;

void CopyBySIMD(const std::vector<float> &src, std::vector<float> &dst) {
  if (src.size() != dst.size()) {
    return;
  }
  for (size_t i = 0, end = src.size(); i < end; i += 8) {
    _mm256_store_ps(&dst[i], _mm256_load_ps(&src[i]));
  }
}

int main() {
  std::vector<float> src(vector_num);
  for (size_t i = 0, e = src.size(); i < e; ++i) {
    src[i] = i;
  }
  std::vector<float> dst(vector_num);
  std::cout << std::hex << reinterpret_cast<long long>(&src[0]) << ","
            << reinterpret_cast<long long>(&dst[0]) << std::endl;

  CopyBySIMD(src, dst);

  return 0;
}
