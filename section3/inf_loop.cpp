#include <iostream>
int main(void) {
  uint64_t sum = 0;
  for (size_t i = 0; i != -1; ++i) {
    sum += i;
  }
  std::cout << sum << std::endl;
  return 0;
}
