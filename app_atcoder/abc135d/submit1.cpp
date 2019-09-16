#include <iostream>
#include <string>
#include <vector>

const int64_t MOD = 1000 * 1000 * 1000 + 7;

int main() {
  std::string s;
  std::cin >> s;

  // i番目の文字を見た時に13との剰余がnになる個数を数え上げる
  std::vector<int64_t> dp((s.length() + 1) * 13);

  dp[0] = 1;

  for (int i = 0, e = s.length(); i < e; ++i) {
    // ?ならvalは-1になる
    int val = -1;
    if (s[i] != '?') val = s[i] - '0';

    // 今がhatenaなら
    if (val == -1) {
      // 次の文字は0-10のどれかで
      for (int next = 0; next < 10; ++next) {
        // 現在地の剰余の結果は0-13のどこかになるので
        for (int here = 0; here < 13; ++here) {
          // here * 10 + nextでひっ算的なことができる
          auto &next_dp = dp[(i + 1) * 13 + ((here * 10 + next) % 13)];
          const auto &here_dp = dp[i * 13 + here];
          next_dp = (next_dp + here_dp) % MOD;
        }
      }
    } else {
      for (int here = 0; here < 13; ++here) {
        auto &next_dp = dp[(i + 1) * 13 + ((here * 10 + val) % 13)];
        const auto &here_dp = dp[i * 13 + here];
        next_dp = (next_dp + here_dp) % MOD;
      }
    }
  }
  std::cout << dp[s.length() * 13 + 5] << std::endl;
  return 0;
}
