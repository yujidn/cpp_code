#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../timer/timer_class.hpp"

void rgb2gray(const cv::Mat &src, cv::Mat &dst) {
  FUNC_TIMER;

  const size_t &rows = src.rows;
  const size_t &cols = src.cols;
  dst = cv::Mat(rows, cols, CV_8UC1);
  for (size_t y = 0; y < rows; ++y) {
    const auto src_row = src.ptr<cv::Vec3b>(y);
    auto dst_row = dst.ptr<uint8_t>(y);
    for (size_t x = 0; x < cols; ++x) {
      // 通常のNTSC加重平均でのグレースケール変換
      // Y=0.298912r+0.586611g+0.114478b
      // 整数倍にする
      // Y=(306r+601g+117b)/1024
      const auto vec3b = src_row[x];
      // OpenCVでは画素にBGRの順番で値が格納されている
      uint32_t temp = 117 * vec3b[0] + 601 * vec3b[1] + 306 * vec3b[2];
      temp >>= 10;
      dst_row[x] = static_cast<uint8_t>(temp);
    }
  }

  return;
}

int main() {
  auto src = cv::imread("gradation_2048x2048.jpg", 1);
  cv::Mat dst;

  rgb2gray(src, dst);

  cv::imwrite("gradation_gray_by_normal.jpg", dst);

  return 0;
}

