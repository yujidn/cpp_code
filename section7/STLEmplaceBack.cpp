#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^8
const uint64_t vector_num = 1000 * 1000 * 100;

void vector_emplace_back(std::vector<int> &vec, const int size) {
  FUNC_TIMER;
  for (size_t i = 0; i < size; ++i) {
    vec.emplace_back(i);
  }
}
void list_emplace_back(std::list<int> &list, const int size) {
  FUNC_TIMER;
  for (size_t i = 0; i < size; ++i) {
    list.emplace_back(i);
  }
}
void deque_emplace_back(std::deque<int> &deque, const int size) {
  FUNC_TIMER;
  for (size_t i = 0; i < size; ++i) {
    deque.emplace_back(i);
  }
}

int main() {
  for (uint64_t size = 1000; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<int> vec;
    std::list<int> list;
    std::deque<int> deque;

    vector_emplace_back(vec, size);
    list_emplace_back(list, size);
    deque_emplace_back(deque, size);
  }

  return 0;
}
