#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<std::string> sn(n);
  for (auto &s : sn) {
    std::cin >> s;
    std::sort(&s[0], &s[s.length()]);
  }

  std::sort(sn.begin(), sn.end());

  int64_t count = 0;
  int64_t local_count = 0;
  for (int i = 1; i < n; ++i) {
    if (sn[i - 1] == sn[i]) {
      ++local_count;
    } else {
      if (local_count > 0) {
        count += local_count * (local_count + 1) / 2;
      }
      local_count = 0;
    }
  }
  if (local_count > 0) {
    count += local_count * (local_count + 1) / 2;
  }

  std::cout << count << std::endl;

  return 0;
}
