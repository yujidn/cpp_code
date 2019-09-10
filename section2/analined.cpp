#include <immintrin.h>
#include <iostream>

struct aligned {
  char a;
  int b;
  char c[512];
};

__m256 loadu(float* ptr) { return _mm256_loadu_ps(ptr); }
__m256 load(float* ptr) { return _mm256_load_ps(ptr); }

int main() {
  aligned align;
  std::cout << std::hex << (int64_t)(&align.a) << std::endl;
  std::cout << std::hex << (int64_t)(&align.b) << std::endl;
  auto ptr = &align.c[0];
  std::cout << std::hex << (int64_t)(ptr) << std::endl;

  std::cout << 1 << std::endl;
  auto l1 = loadu((float*)ptr);
  std::cout << 2 << std::endl;
  auto l2 = load((float*)ptr);
  std::cout << 3 << std::endl;

  return 0;
}

