#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^7
const uint64_t vector_num = 1000 * 1000 * 10;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

int main() {
  timer t;
  for (uint64_t size = 100; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<int> vec;
    std::list<int> list;
    std::deque<int> deque;

    for (size_t s = 0; s < size; ++s) {
      int r = int_rand(engine);
      vec.push_back(r);
      list.push_back(r);
      deque.push_back(r);
    }

    t.restart();
    std::stable_sort(vec.begin(), vec.end());

    t.print("vector_stable_sort");
    t.restart();

    std::stable_sort(deque.begin(), deque.end());

    t.print("deque_stable_sort");
  }
  return 0;
}
