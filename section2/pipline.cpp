#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.push_back(6);

  {
    // タイマースタート
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();

    int sum = 0;
    for (size_t i = 0; i < 1000000000; ++i) {
      for (size_t j = 0; j < 1000000000; ++j) {
        sum += vec[0];
        sum += vec[1];
        sum += vec[2];
        sum += vec[3];
        sum += vec[4];
        sum += vec[5];
      }
    }

    // タイマーエンド
    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();

    std::cout << sum << std::endl;

    // タイマー間の時間をns単位で取得
    auto count =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    // アクセス範囲と時間を表示する
    std::cout << count << std::endl;
  }

  {
    // タイマースタート
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();

    int sum = 0;
    for (size_t i = 0; i < 1000000000; ++i) {
      for (size_t j = 0; j < 1000000000; ++j) {
        int a = vec[0] + vec[1];
        int b = vec[2] + vec[3];
        int c = vec[4] + vec[5];
        sum += a;
        b += c;
        sum += b;
      }
    }

    // タイマーエンド
    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();

    std::cout << sum << std::endl;

    // タイマー間の時間をns単位で取得
    auto count =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    // アクセス範囲と時間を表示する
    std::cout << count << std::endl;
  }

  return 0;
}
