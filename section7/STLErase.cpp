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
// 10^3
const uint64_t erase_num = 1000;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

void vector_erase(std::vector<int> &vec, const std::vector<int> &erase_index) {
  FUNC_TIMER;
  for (const auto &index : erase_index) {
    vec.erase(vec.begin() + (index % vec.size()));
  }
}
void list_erase(std::list<int> &list, const std::vector<int> &erase_index) {
  FUNC_TIMER;
  for (const auto &index : erase_index) {
    // これをやってしまうと激遅なので注意
    // list.erase(std::next(list.begin(), index % vec.size()), 1);
    list.erase(std::next(list.begin(), 0));
  }
}
void deque_erase(std::deque<int> &deque, const std::vector<int> &erase_index) {
  FUNC_TIMER;
  for (const auto &index : erase_index) {
    deque.erase(deque.begin() + (index % deque.size()));
  }
}
void map_erase(std::map<int, int> &map, const std::vector<int> &erase_index) {
  FUNC_TIMER;
  const auto size = map.size();
  for (const auto &index : erase_index) {
    map.erase(index % map.size());
  }
}
void unorderd_map_erase(std::unordered_map<int, int> &unorderd_map,
                        const std::vector<int> &erase_index) {
  FUNC_TIMER;
  const auto size = unorderd_map.size();
  for (const auto &index : erase_index) {
    unorderd_map.erase(index % unorderd_map.size());
  }
}

int main() {
  std::vector<int> erase_index;
  for (uint64_t i = 0; i < erase_num; ++i) {
    erase_index.push_back(int_rand(engine));
  }

  for (uint64_t size = 1000; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<int> vec(size);
    std::list<int> list(size);
    std::deque<int> deque(size);
    std::map<int, int> map;
    for (uint64_t i = 0; i < size; ++i) {
      map.insert(std::make_pair(i, i));
    }
    std::unordered_map<int, int> unorderd_map;
    for (uint64_t i = 0; i < size; ++i) {
      unorderd_map.insert(std::make_pair(i, i));
    }

    vector_erase(vec, erase_index);
    list_erase(list, erase_index);
    deque_erase(deque, erase_index);
    map_erase(map, erase_index);
    unorderd_map_erase(unorderd_map, erase_index);
  }

  return 0;
}
