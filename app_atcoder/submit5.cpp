#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

// ハッシュ計算で使う素数
constexpr int prime[] = {2,  3,  5,  7,  11, 13,  17,  19, 23, 29,
                         31, 37, 41, 43, 47, 53,  59,  61, 67, 71,
                         73, 79, 83, 89, 97, 101, 103, 107};

constexpr size_t alphabet = 26;
constexpr size_t str_len = 10;

inline int64_t hash(char *str, int start, int end) {
  int64_t result = 1;

  // アルファベット1文字ごとに素数を割り当てて掛け算結果をハッシュ値にする
  // オーバーフローしない限りは完全ハッシュ
  for (size_t i = start; i < end; ++i) {
    result *= prime[str[i] - 'a'];
  }

  return result;
}

int main() {
  int n;
  scanf("%d", &n);

  // 最大入力数*1行の文字数(改行込み)
  char input[100000 * 11 + 5];

  // 文字列の一括入力
  fread(input, sizeof(char), sizeof(char) * 11 * n, stdin);

  std::unordered_map<int64_t, int64_t> map;
  int64_t count = 0;
  for (int i = 0; i < n; ++i) {
    auto key = hash(input, i * 11 + 1, i * 11 + 10 + 1);

    if (map.count(key) == 0) {
      map[key] = 0;
    } else {
      auto &val = map[key];
      count += (++val);
    }
  }
  printf("%ld\n", count);

  return 0;
}
