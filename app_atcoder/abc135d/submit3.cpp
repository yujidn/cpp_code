#include <iostream>
#include <string>
#include <vector>

const int64_t MOD = 1000 * 1000 * 1000 + 7;

template <uint8_t max_value, uint8_t mod_value>
struct index_mod {
  uint8_t mod[max_value];
  constexpr index_mod() : mod() {
    for (size_t i = 0; i < max_value; ++i) {
      mod[i] = i % mod_value;
    }
  }
};

int main() {
  std::string s;
  std::cin >> s;

  // i番目の文字を見た時に13との剰余がnになる個数を数え上げる
  std::vector<int64_t> dp(2 * 13);

  constexpr index_mod<13 * 10, 13> imod;

  {  // テーブル初期化
    int val = -1;
    if (s[0] != '?') val = s[0] - '0';
    if (val == -1) {
      for (size_t i = 0; i < 10; ++i) {
        dp[i % 13] = 1;
      }
    } else {
      dp[val % 13] = 1;
    }
    // % 13は不要だけど定義に帰るため
  }

  for (size_t i = 1, e = s.length(); i < e; ++i) {
    int val = -1;
    if (s[i] != '?') val = s[i] - '0';
    if (val == -1) {
      for (size_t pre = 0; pre < 13; ++pre) {
        const auto &pre_dp = dp[pre];
        const auto pindex = pre * 10;
        for (size_t here = 0; here < 10; ++here) {
          auto &here_dp = dp[13 + imod.mod[pindex + here]];
          here_dp = here_dp + pre_dp;
        }
      }
    } else {
      for (size_t pre = 0; pre < 13; ++pre) {
        auto &here_dp = dp[13 + imod.mod[pre * 10 + val]];
        const auto &pre_dp = dp[pre];
        here_dp = pre_dp;
      }
    }

    for (size_t i = 0; i < 13; ++i) {
      dp[i] = dp[13 + i] % MOD;
      // dp[i] = dp[13 + i];
      dp[13 + i] = 0;
    }
  }

  std::cout << dp[5] % MOD << std::endl;
  return 0;
}
