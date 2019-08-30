#include <iostream>

int main() {
  int sum = 0;
  for (int i = 0; i < 100000; ++i) {
    for (int j = 0; j < 100000; ++j) sum += j;
  }
  std::cout << sum << std::endl;
  return 0;
}
