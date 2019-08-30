#include <emmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <nmmintrin.h>
#include <pmmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>

#include <iostream>

#include "../timer/timer_class.hpp"

union m256i_union {
  __m256i m;
  char c[32];
  short s[16];
  long l[8];
  long long ll[4];
};

union m256_union {
  __m256 m;
  float f[8];
  double d[4];
};

int main() {
  m256_union src1, src2, dst;
  src1.m = _mm256_setr_ps(1, 2, 3, 4, 5, 6, 7, 8);
  src2.m = _mm256_setr_ps(5, 6, 7, 8, 9, 8, 7, 6);

  auto cout = [](const m256_union &dst) {
    auto address = reinterpret_cast<long long>(&dst);
    for (size_t i = 0; i < sizeof(__m256) / sizeof(float); ++i) {
      std::cout << dst.f[i] << ",";
    }
    std::cout << std::endl;
  };

  cout(src1);

  // 内部変数に手軽にアクセスできる
  src1.f[0] = 3;
  src1.f[4] = src2.f[4];

  cout(src1);

  // アライメントアドレスに配置される
  std::cout << std::hex << reinterpret_cast<long long>(&src1.m) << std::endl;
  std::cout << std::hex << reinterpret_cast<long long>(&src1.f[0]) << std::endl;
  std::cout << std::hex << reinterpret_cast<long long>(&src1.d[0]) << std::endl;

  std::cout << "---add---" << std::endl;
  dst.m = _mm256_add_ps(src1.m, src2.m);
  cout(dst);
  std::cout << "---sub---" << std::endl;
  dst.m = _mm256_sub_ps(src1.m, src2.m);
  cout(dst);
  std::cout << "---mul---" << std::endl;
  dst.m = _mm256_mul_ps(src1.m, src2.m);
  cout(dst);
  std::cout << "---div---" << std::endl;
  dst.m = _mm256_div_ps(src1.m, src2.m);
  cout(dst);

  return 0;
}
