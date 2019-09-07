// mmx
#include <mmintrin.h>
// sse
#include <xmmintrin.h>
// sse2
#include <emmintrin.h>
// sse3
#include <pmmintrin.h>
// ssse3
#include <tmmintrin.h>
// sse4.1
#include <smmintrin.h>
// sse4.2
#include <nmmintrin.h>
// avx, avx2, avx-512
#include <immintrin.h>

#include <iostream>

#include "../timer/timer_class.hpp"

int main() {
  {
    // 128ビット浮動小数点型(floatを4つ、doubleを2つ)
    __m128 m128;
    // 128ビット整数型(charを16、shortを8つ、longを4つ、longlongを2つ)
    __m128i m128i;
    // 256ビット浮動小数点型(floatを8つ、doubleを4つ)
    __m256 m256;
    // 128ビット整数型(charを32、shortを16つ、longを8つ、longlongを4つ)
    __m256i m256i;

    std::cout << std::hex;
    std::cout << "type    sizeof address" << std::endl;
    std::cout << "__m128  0x" << sizeof(__m128) << " 0x"
              << reinterpret_cast<long long>(&m128) << std::endl;
    std::cout << "__m128i 0x" << sizeof(__m128i) << " 0x"
              << reinterpret_cast<long long>(&m128i) << std::endl;
    std::cout << "__m256  0x" << sizeof(__m256) << " 0x"
              << reinterpret_cast<long long>(&m256) << std::endl;
    std::cout << "__m256i 0x" << sizeof(__m256i) << " 0x"
              << reinterpret_cast<long long>(&m256i) << std::endl;
  }
  __m128 src1, src2, dst;
  src1 = _mm_setr_ps(1, 2, 3, 4);
  src2 = _mm_setr_ps(5, 6, 7, 8);

  auto cout = [](const __m128 &dst) {
    auto address = reinterpret_cast<long long>(&dst);
    for (size_t i = 0; i < sizeof(__m128) / sizeof(float); ++i) {
      auto pointer = reinterpret_cast<float *>(address + sizeof(float) * i);
      std::cout << *pointer << ",";
    }
    std::cout << std::endl;
  };

  std::cout << "---add---" << std::endl;
  dst = _mm_add_ps(src1, src2);
  cout(dst);
  std::cout << "---sub---" << std::endl;
  dst = _mm_sub_ps(src1, src2);
  cout(dst);
  std::cout << "---mul---" << std::endl;
  dst = _mm_mul_ps(src1, src2);
  cout(dst);
  std::cout << "---div---" << std::endl;
  dst = _mm_div_ps(src1, src2);
  cout(dst);

  return 0;
}
