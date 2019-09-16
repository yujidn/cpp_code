#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

const uint64_t MOD = 1000 * 1000 * 1000 + 7;

template <uint8_t mod_value>
struct index_mod {
  uint8_t mod[mod_value][mod_value];
  constexpr index_mod() : mod() {
    for (size_t i = 0; i < mod_value; ++i) {
      for (size_t j = 0; j < mod_value; ++j) {
        mod[i][j] = (i * 10 + j) % mod_value;
      }
    }
  }
};

template <uint8_t mod_value>
struct sub_index {
  uint8_t index[mod_value][mod_value - 10];
  constexpr sub_index() : index() {
    auto value = 0;
    uint8_t in[mod_value] = {0};
    for (size_t i = 0; i < mod_value; ++i) {
      value += 10;
      for (size_t j = 0; j < mod_value - 10; ++j) {
        // index[i][j] = (value + j) % mod_value;
        auto v = (value + j) % mod_value;
        index[v][in[v]] = i;
        ++in[v];
      }
    }
  }
};

char s[100005];

int main() {
  // auto start = std::chrono::system_clock::now();

  scanf("%s", s);

  // std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(
  //                  std::chrono::system_clock::now() - start)
  //                  .count()
  //           << std::endl;
  // i番目の文字を見た時に13との剰余がnになる個数を数え上げる
  std::vector<uint64_t> dp(2 * 13);

  constexpr index_mod<13> imod;
  constexpr sub_index<13> sindex;

  // for (size_t i = 0; i < 13; ++i) {
  // for (size_t j = 0; j < 13; ++j) {
  //   std::cout << (int)imod.mod[i][j] << ",";
  // }
  // std::cout << std::endl;
  // }
  // for (size_t i = 0; i < 13; ++i) {
  // for (size_t j = 0; j < 3; ++j) {
  //   std::cout << (int)sindex.index[i][j] << ",";
  // }
  // std::cout << std::endl;
  // }

  uint64_t row_sum = 0;

  {  // テーブル初期化
    int val = -1;
    if (s[0] != '?') val = s[0] - '0';
    if (val == -1) {
      for (size_t i = 0; i < 10; ++i) {
        dp[i % 13] = 1;
      }
      row_sum = 10;
    } else {
      dp[val % 13] = 1;
      row_sum = 1;
    }
    // % 13は不要だけど定義に帰るため
  }

  // std::cout <<
  // std::chrono::duration_cast<std::chrono::nanoseconds>(
  //                  std::chrono::system_clock::now() - start)
  //                  .count()
  //           << std::endl;
  for (size_t i = 1, e = strlen(s); i < e; ++i) {
    int val = -1;
    if (s[i] != '?') val = s[i] - '0';
    if (val == -1) {
      auto temp_sum = row_sum + 3 * MOD;
      for (size_t here = 0; here < 13; ++here) {
        uint64_t no_need = 0;
        for (size_t j = 0; j < 3; ++j) {
          no_need += dp[sindex.index[here][j]];
        }
        dp[13 + here] = temp_sum - no_need;
      }
    } else {
      for (size_t pre = 0; pre < 13; ++pre) {
        dp[13 + imod.mod[pre][val]] = dp[pre];
      }
    }

    //     for (int i = 0; i < 2; ++i) {
    //     for (int j = 0; j < 13; ++j) {
    //       std::cout << dp[i * 13 + j] << ",";
    //     }
    //     std::cout << std::endl;
    //   }
    //
    row_sum = 0;
    for (size_t i = 0; i < 13; ++i) {
      dp[i] = dp[13 + i] % MOD;
      row_sum += dp[13 + i];
      // dp[i] = dp[13 + i];
    }
    row_sum %= MOD;
  }

  // std::cout <<
  // std::chrono::duration_cast<std::chrono::nanoseconds>(
  //                  std::chrono::system_clock::now() - start)
  //                  .count()
  //           << std::endl;
  // std::cout << dp[5] % MOD << "\n";
  printf("%d\n", dp[5] % MOD);
  return 0;
}
