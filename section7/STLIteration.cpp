#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^8
const uint64_t vector_num = 1000 * 1000 * 100;
int sum = 0;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

void vector_foreach(std::vector<int> &vec) {
  FUNC_TIMER;
  for (const auto &v : vec) {
    sum += v;
  }
}
void list_foreach(std::list<int> &list) {
  FUNC_TIMER;
  for (const auto &l : list) {
    sum += l;
  }
}
void deque_foreach(std::deque<int> &deque) {
  FUNC_TIMER;
  for (const auto &d : deque) {
    sum += d;
  }
}
void map_foreach(std::map<int, int> &map) {
  FUNC_TIMER;
  for (const auto &m : map) {
    sum += m.second;
  }
}

void unorderd_map_foreach(std::unordered_map<int, int> &unordered_map) {
  FUNC_TIMER;
  for (const auto &m : unordered_map) {
    sum += m.second;
  }
}
int main() {
  int64_t sum = 0;
  for (uint64_t size = 100; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "---" << std::endl;
    std::vector<int> vec(size);
    std::list<int> list(size);
    std::deque<int> deque(size);
    std::map<int, int> map;
    for (uint64_t i = 0; i < size; ++i) {
      map.emplace(std::make_pair(i, i));
    }
    std::unordered_map<int, int> unordered_map;
    for (uint64_t i = 0; i < size; ++i) {
      unordered_map.emplace(std::make_pair(i, i));
    }
    vector_foreach(vec);
    list_foreach(list);
    deque_foreach(deque);
    map_foreach(map);
    unorderd_map_foreach(unordered_map);
  }
  std::cout << sum << std::endl;
  return 0;
}
