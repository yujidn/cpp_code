#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

const uint64_t count = 1000000;

int main() {
  // now()関数の実行コストを計測する
  {
    auto start = std::chrono::system_clock::now();
    // タイマースタート
    for (uint64_t i = 0; i < count; ++i) {
      std::chrono::system_clock::now();
    }
    // タイマーエンド
    auto end = std::chrono::system_clock::now();
    std::cout << "[ns] : "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << std::endl;
  }

  // 2回のnow()関数(処理時間を挟むため)と複数回記録時にvectorにpushbackするコスト(reserveなし)
  {
    std::vector<uint64_t> vec;

    auto start = std::chrono::system_clock::now();
    // タイマースタート
    for (uint64_t i = 0; i < count; ++i) {
      auto s = std::chrono::system_clock::now();
      auto e = std::chrono::system_clock::now();
      vec.push_back(
          std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count());
    }
    // タイマーエンド
    auto end = std::chrono::system_clock::now();
    std::cout << "[ns] : "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << std::endl;
  }

  // 2回のnow()関数(処理時間を挟むため)と複数回記録時にvectorにpushbackするコスト(reserveあり)
  {
    std::vector<uint64_t> vec;
    vec.reserve(count);

    auto start = std::chrono::system_clock::now();
    // タイマースタート
    for (uint64_t i = 0; i < count; ++i) {
      auto s = std::chrono::system_clock::now();
      auto e = std::chrono::system_clock::now();
      vec.push_back(
          std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count());
    }
    // タイマーエンド
    auto end = std::chrono::system_clock::now();
    std::cout << "[ns] : "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << std::endl;
  }

  return 0;
}
