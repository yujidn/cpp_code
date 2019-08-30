#include <iostream>
#include <vector>

const size_t size = 1000000;
int func1() {
  int sum = 0;
  std::vector<int> vec(size);
  for (size_t i = 0; i < size; ++i) {
    vec[i] = i + 5;
  }

  for (const auto &i : vec) {
    sum += i;
  }
  return sum;
}

int func2() {
  int sum = 0;
  std::vector<int> vec(size);
  for (size_t i = 0; i < size; ++i) {
    vec[i] = i + 10;
  }

  for (auto i : vec) {
    sum += i;
  }
  return sum;
}

int main() {
  int sum = 0;
  for (size_t i = 0; i < 100; ++i) {
    sum += func1();
    sum += func2();
  }
  std::cout << sum << std::endl;
  return 0;
}
