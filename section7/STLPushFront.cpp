#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^8
const uint64_t vector_num = 1000 * 1000 * 100;

void list_push_front(std::list<int> &list, const int size) {
  FUNC_TIMER;
  for (size_t i = 0; i < size; ++i) {
    list.push_front(i);
  }
}
void deque_push_front(std::deque<int> &deque, const int size) {
  FUNC_TIMER;
  for (size_t i = 0; i < size; ++i) {
    deque.push_front(i);
  }
}

int main() {
  for (uint64_t size = 1000; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::list<int> list;
    std::deque<int> deque;

    list_push_front(list, size);
    deque_push_front(deque, size);
  }
  return 0;
}

