#include <emmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <nmmintrin.h>
#include <pmmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../timer/timer_class.hpp"

union m128i_union {
  __m128i m;
  __m128 mf;
  char c[16];
  short s[8];
  long l[4];
  long long ll[2];
};

void rgb2gray(const cv::Mat &src, cv::Mat &dst) {
  FUNC_TIMER;

  const size_t &rows = src.rows;
  const size_t &cols = src.cols;
  dst = cv::Mat(rows, cols, CV_8UC1);

  constexpr m128i_union mask1 = {.l = {117, 601, 306, 117}};
  constexpr m128i_union mask2 = {.l = {601, 306, 117, 601}};
  constexpr m128i_union mask3 = {.l = {306, 117, 601, 306}};
  constexpr m128i_union sub = {.l = {1024, 1024, 1024, 1024}};

  constexpr int8_t zp = 1 << 7;

  constexpr m128i_union shuffle_1 = {
      .c = {0, zp, zp, zp, 1, zp, zp, zp, 2, zp, zp, zp, 3, zp, zp, zp}};
  constexpr m128i_union shuffle_2 = {
      .c = {4, zp, zp, zp, 5, zp, zp, zp, 6, zp, zp, zp, 7, zp, zp, zp}};
  constexpr m128i_union shuffle_3 = {
      .c = {8, zp, zp, zp, 9, zp, zp, zp, 10, zp, zp, zp, 11, zp, zp, zp}};
  constexpr m128i_union result = {.c = {
                                      0,
                                      4,
                                      8,
                                      12,
                                      zp,
                                      zp,
                                      zp,
                                      zp,
                                      zp,
                                      zp,
                                      zp,
                                      zp,
                                  }};

  for (size_t y = 0; y < rows; ++y) {
    const auto src_row = src.ptr<uint8_t>(y);
    auto dst_row = dst.ptr<uint8_t>(y);
    for (size_t x = 0; x < cols; x += 4) {
      auto load = _mm_loadu_si128((__m128i *)(&src_row[3 * x]));
      m128i_union p1, p2, p3;
      p1.m = _mm_shuffle_epi8(load, shuffle_1.m);
      p2.m = _mm_shuffle_epi8(load, shuffle_2.m);
      p3.m = _mm_shuffle_epi8(load, shuffle_3.m);
      p1.m = _mm_mul_epi32(p1.m, mask1.m);
      p2.m = _mm_mul_epi32(p2.m, mask2.m);
      p3.m = _mm_mul_epi32(p3.m, mask3.m);
      m128i_union b = {.l = {p1.l[0], p1.l[3], p2.l[2], p3.l[1]}};
      m128i_union g = {.l = {p1.l[1], p2.l[0], p2.l[3], p3.l[2]}};
      m128i_union r = {.l = {p1.l[2], p2.l[1], p3.l[0], p3.l[3]}};
      b.m = _mm_add_epi32(b.m, g.m);
      b.m = _mm_add_epi32(b.m, r.m);
      b.m = _mm_sub_epi32(b.m, sub.m);
      b.m = _mm_shuffle_epi8(b.m, result.m);
      _mm_store_ss((float *)&dst_row[x], b.mf);
    }
  }

  return;
}

int main() {
  auto src = cv::imread("gradation_2048x2048.jpg", 1);
  cv::Mat dst;

  rgb2gray(src, dst);

  cv::imwrite("gradation_gray_by_simd.jpg", dst);

  return 0;
}

