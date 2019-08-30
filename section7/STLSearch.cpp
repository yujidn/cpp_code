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
// 10^2
const uint64_t search_num = 100;
int64_t sum = 0;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

void vector_search(const std::vector<int> &vec,
                   const std::vector<int> &search) {
  FUNC_TIMER;
  auto size = vec.size();
  for (const auto &key : search) {
    auto result = *std::upper_bound(vec.begin(), vec.end(), key % size);
    sum += result;
  }
}
void list_search(const std::list<int> &list, const std::vector<int> &search) {
  FUNC_TIMER;
  auto size = list.size();
  for (const auto &key : search) {
    auto result = *std::upper_bound(list.begin(), list.end(), key % size);
    sum += result;
  }
}
void deque_search(const std::deque<int> &deque,
                  const std::vector<int> &search) {
  FUNC_TIMER;
  auto size = deque.size();
  for (const auto &key : search) {
    auto result = *std::upper_bound(deque.begin(), deque.end(), key % size);
    sum += result;
  }
}
void map_search(const std::map<int, int> &map, const std::vector<int> &search) {
  FUNC_TIMER;
  auto size = map.size();
  for (const auto &key : search) {
    sum += map.at(key % size);
  }
}
void unordered_search(const std::unordered_map<int, int> &map,
                      const std::vector<int> &search) {
  FUNC_TIMER;
  auto size = map.size();
  for (const auto &key : search) {
    sum += map.at(key % size);
  }
}

int main() {
  int64_t sum = 0;
  std::vector<int> search;
  for (uint64_t i = 0; i < search_num; ++i) {
    search.push_back(int_rand(engine));
  }
  for (uint64_t size = 100; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<int> vec;
    std::list<int> list;
    std::deque<int> deque;
    std::map<int, int> map;
    std::unordered_map<int, int> unordered_map;
    for (size_t s = 0; s < size; ++s) {
      vec.push_back(s);
      list.push_back(s);
      deque.push_back(s);
      map.insert(std::make_pair(s, s));
      unordered_map.insert(std::make_pair(s, s));
    }

    vector_search(vec, search);
    list_search(list, search);
    deque_search(deque, search);
    map_search(map, search);
    unordered_search(unordered_map, search);
  }

  return 0;
}

