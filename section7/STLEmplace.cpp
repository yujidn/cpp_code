#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const uint64_t insert_num = 1000;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

void vector_emplace(std::vector<int> &vec,
                    const std::vector<int> &insert_index) {
  FUNC_TIMER;
  for (const auto &index : insert_index) {
    vec.emplace(vec.begin() + (index % vec.size()), 1);
  }
}
void list_emplace(std::list<int> &list, const std::vector<int> &insert_index) {
  FUNC_TIMER;
  for (const auto &index : insert_index) {
    // これをやってしまうと激遅なので注意
    // list.emplace(std::next(list.begin(), index % vec.size()), 1);
    list.emplace(std::next(list.begin(), 0), 1);
  }
}
void deque_emplace(std::deque<int> &deque,
                   const std::vector<int> &insert_index) {
  FUNC_TIMER;
  for (const auto &index : insert_index) {
    deque.emplace(deque.begin() + (index % deque.size()), 1);
  }
}
void map_emplace(std::map<int, int> &map,
                 const std::vector<int> &insert_index) {
  FUNC_TIMER;
  const auto size = map.size();
  for (const auto &index : insert_index) {
    map.emplace(std::make_pair((index % map.size()) + size, index + size));
  }
}
void unorderd_map_emplace(std::unordered_map<int, int> &unorderd_map,
                          const std::vector<int> &insert_index) {
  FUNC_TIMER;
  const auto size = unorderd_map.size();
  for (const auto &index : insert_index) {
    unorderd_map.emplace(
        std::make_pair((index % unorderd_map.size()) + size, index + size));
  }
}

int main() {
  std::vector<int> insert_index;
  for (uint64_t i = 0; i < insert_num; ++i) {
    insert_index.push_back(int_rand(engine));
  }

  for (uint64_t size = 1; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "---" << std::endl;
    std::vector<int> vec(size);
    std::list<int> list(size);
    std::deque<int> deque(size);
    std::map<int, int> map;
    for (uint64_t i = 0; i < size; ++i) {
      map.emplace(std::make_pair(i, i));
    }
    std::unordered_map<int, int> unorderd_map;
    for (uint64_t i = 0; i < size; ++i) {
      unorderd_map.emplace(std::make_pair(i, i));
    }

    vector_emplace(vec, insert_index);
    list_emplace(list, insert_index);
    deque_emplace(deque, insert_index);
    map_emplace(map, insert_index);
    unorderd_map_emplace(unorderd_map, insert_index);
  }

  return 0;
}
