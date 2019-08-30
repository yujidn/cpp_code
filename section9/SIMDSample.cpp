#include <immintrin.h>
#include <cfloat>
#include <iostream>
#include <vector>

#include "../timer/timer_class.hpp"

const size_t vector_num = 1024 * 1024;

void VectorAdd(const std::vector<float> &src1, const std::vector<float> &src2,
               std::vector<float> &dst) {
  FUNC_TIMER;
  if (src1.size() != src2.size()) {
    return;  // なんかエラーくらいだそうよ…
  }
  if (src1.size() != dst.size()) {
    return;
  }
  const size_t end = src1.size();
  for (size_t i = 0; i < end; ++i) {
    dst[i] = src1[i] + src2[i];
  }
}

void VectorAddBySIMD(const std::vector<float> &src1,
                     const std::vector<float> &src2, std::vector<float> &dst) {
  FUNC_TIMER;
  if (src1.size() != src2.size()) {
    return;
  }
  if (src1.size() != dst.size()) {
    return;
  }
  const size_t end = src1.size();
  for (size_t i = 0; i < end; i += 8) {
    // 配列から256bit持ってくる
    __m256 s1 = _mm256_loadu_ps(&src1[i]);
    __m256 s2 = _mm256_loadu_ps(&src2[i]);
    // 256bit内の8個のfloatを一気に加算
    __m256 result = _mm256_add_ps(s1, s2);
    // 計算結果を配列に入れる
    _mm256_storeu_ps(&dst[i], result);
  }
}

int main() {
  std::vector<float> src1(vector_num);
  std::vector<float> src2(vector_num);
  for (size_t i = 0, e = src1.size(); i < e; ++i) {
    src1[i] = i;
    src2[i] = i;
  }

  std::vector<float> dst(vector_num), dstBySIMD(vector_num);
  VectorAdd(src1, src2, dst);
  VectorAddBySIMD(src1, src2, dstBySIMD);

  // 簡単にチェック
  for (size_t i = 0, e = dst.size(); i < e; ++i) {
    if (std::abs(dst[i] - dstBySIMD[i]) > DBL_EPSILON) {
      std::cout << "diff value!, " << dst[i] << "," << dstBySIMD[i]
                << std::endl;
    }
  }
  return 0;
}
