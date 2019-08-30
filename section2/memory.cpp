#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// 10^9
const uint64_t vector_num = 100000000;
// 10^7
const uint64_t access_num = 1000000;
std::random_device seed_gen;

auto engine = std::mt19937_64(seed_gen());

int main() {
  // 仮データを作る
  std::vector<int> vec(vector_num);
  // 仮データにアクセスする要素を貯める用
  std::vector<int> access;
  access.reserve(access_num);

  // 仮データにアクセスする最大値を決めてループする
  for (uint64_t size = 1; size <= vector_num; size = size * 10) {
    // 0～size未満の一様分布
    auto rand = std::uniform_int_distribution<>(0, size);

    // 仮データにアクセスする添え字配列を作る 添え字の値域は0~size未満
    access.clear();
    for (size_t i = 0; i < access_num; ++i) {
      access.push_back(rand(engine));
    }

    // タイマースタート
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();
    // 仮データに適当にアクセスする
    for (const auto &acc : access) {
      vec[acc] += 1;
    }
    // タイマーエンド
    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();

    // タイマー間の時間をns単位で取得
    auto count =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    // アクセス範囲と時間を表示する
    std::cout << size << "," << count << std::endl;
  }
  return 0;
}
