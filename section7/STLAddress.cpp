#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

template <typename T>
void address(const T& stl) {
  std::vector<long long> vec;
  for (const auto& s : stl) {
    vec.push_back(reinterpret_cast<long long>(&s));
  }

  for (int i = 1, end = vec.size(); i < end; ++i) {
    std::cout << vec[i] - vec[i - 1] << ",";
  }
  std::cout << std::endl;
}

int main() {
  const int size = 10;

  std::vector<int> vec;
  std::list<int> list;
  std::deque<int> deque;
  std::deque<std::array<int, 128>> deque2;
  std::map<int, int> map;
  std::unordered_map<int, int> unordered_map;
  for (size_t s = 0; s < size; ++s) {
    vec.push_back(s);
    list.push_back(s);
    deque.push_back(s);
    deque2.push_back(std::array<int, 128>());
    map.insert(std::make_pair(s, s));
    unordered_map.insert(std::make_pair(s, s));
  }

  address(vec);
  address(list);
  address(deque);
  address(deque2);
  address(map);
  address(unordered_map);

  return 0;
}
