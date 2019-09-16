#include <iostream>
#include <string>
#include <vector>

const uint64_t MOD = 1000 * 1000 * 1000 + 7;

template <uint8_t max_value, uint8_t mod_value>
struct index_mod {
  uint8_t mod[max_value];
  constexpr index_mod() : mod() {
    for (size_t i = 0; i < max_value; ++i) {
      mod[i] = i % mod_value;
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

int main() {
  std::string s;
  std::cin >> s;

  // i番目の文字を見た時に13との剰余がnになる個数を数え上げる
  std::vector<uint64_t> dp(2 * 13);

  constexpr index_mod<13 * 10, 13> imod;
  constexpr sub_index<13> sindex;

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

  for (size_t i = 1, e = s.length(); i < e; ++i) {
    int val = -1;
    if (s[i] != '?') val = s[i] - '0';
    if (val == -1) {
      for (size_t pre = 0; pre < 13; ++pre) {
        auto temp_sum = row_sum + 3 * MOD;
        for (size_t j = 0; j < 3; ++j) {
          temp_sum -= dp[sindex.index[pre][j]];
        }
        dp[13 + pre] = temp_sum;
      }
    } else {
      for (size_t pre = 0; pre < 13; ++pre) {
        auto &here_dp = dp[13 + imod.mod[pre * 10 + val]];
        const auto &pre_dp = dp[pre];
        here_dp = pre_dp;
      }
    }

    row_sum = 0;
    for (size_t i = 0; i < 13; ++i) {
      dp[i] = dp[13 + i] % MOD;
      row_sum += dp[i];
      // dp[i] = dp[13 + i];
      dp[13 + i] = 0;
    }
    row_sum %= MOD;
  }

  std::cout << dp[5] % MOD << std::endl;
  return 0;
}
