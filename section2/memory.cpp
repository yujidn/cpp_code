#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// 10^9
const uint64_t vector_num = 1000 * 1000 * 1000;
// 10^6
const uint64_t access_num = 1000 * 1000;
std::random_device seed_gen;

auto engine = std::mt19937_64(seed_gen());

int main() {
  // 仮データを作る
  std::vector<int> vec(vector_num);
  // 仮データにアクセスする要素を貯める用
  std::vector<int> access(access_num);

  uint64_t sum = 0;

  // 仮データにアクセスする最大値を決めてループする
  for (uint64_t size = 1; size <= vector_num; size = size * 10) {
    // 0～size未満の一様分布
    // 配列内のアクセスする範囲を限定する
    auto rand = std::uniform_int_distribution<>(0, size);

    // どこにアクセスするかを決める配列を作る
    for (auto &acc : access) {
      acc = rand(engine);
    }

    // タイマースタート
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();
    // 仮データに適当にアクセスする
    for (const auto &acc : access) {
      // accは0~sizeの間からランダムになる
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

    // 最適化で時間計測部分が消えないようにする
    for (const auto &v : vec) {
      sum += v;
    }
  }
  std::cout << sum << std::endl;
  return 0;
}
