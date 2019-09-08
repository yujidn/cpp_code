#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "../timer/timer_class.hpp"

int main() {
  auto src = cv::imread("gradation_2048x2048.jpg", 1);
  cv::Mat dst;

  timer t;
  cv::cvtColor(src, dst, CV_BGR2GRAY);
  t.print("by_opencv");

  cv::imwrite("gradation_gray_by_opencv.jpg", dst);

  return 0;
}

