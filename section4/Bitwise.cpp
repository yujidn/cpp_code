#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^6
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 100);
auto shift_rand = std::uniform_int_distribution<>(1, 31);

template <typename T>
void And(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first & v.second;
  }
  return;
}
template <typename T>
void Or(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first | v.second;
  }
  return;
}
template <typename T>
void Not(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = ~v.first;
  }
  return;
}
template <typename T>
void Exclusive(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first ^ v.second;
  }
  return;
}
template <typename T>
void Lshift(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first << v.second;
  }
  return;
}
template <typename T>
void Rshift(std::vector<std::pair<T, T>> &vec) {
  for (auto &v : vec) {
    v.first = v.first >> v.second;
  }
  return;
}

int main() {
  std::vector<std::pair<int, int>> vec_i(vector_num);
  std::vector<std::pair<int64_t, int64_t>> vec_l(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec_i[i] = std::make_pair(int_rand(engine), shift_rand(engine));
    vec_l[i] = std::make_pair(static_cast<int64_t>(int_rand(engine)),
                              static_cast<int64_t>(shift_rand(engine)));
  }
  std::cout << "---long---" << std::endl;
  loop_time("long and", loop, (void (*)(decltype(vec_i) &))(And), vec_i);
  loop_time("long or", loop, (void (*)(decltype(vec_i) &))(Or), vec_i);
  loop_time("long not", loop, (void (*)(decltype(vec_i) &))(Not), vec_i);
  loop_time("long exclusive", loop, (void (*)(decltype(vec_i) &))(Exclusive),
            vec_i);
  loop_time("long lshift", loop, (void (*)(decltype(vec_i) &))(Lshift), vec_i);
  loop_time("long rshift", loop, (void (*)(decltype(vec_i) &))(Rshift), vec_i);

  std::cout << "---long long---" << std::endl;
  loop_time("long long and", loop, (void (*)(decltype(vec_l) &))(And), vec_l);
  loop_time("long long or", loop, (void (*)(decltype(vec_l) &))(Or), vec_l);
  loop_time("long long not", loop, (void (*)(decltype(vec_l) &))(Not), vec_l);
  loop_time("long long exclusive", loop,
            (void (*)(decltype(vec_l) &))(Exclusive), vec_l);
  loop_time("long long lshift", loop, (void (*)(decltype(vec_l) &))(Lshift),
            vec_l);
  loop_time("long long rshift", loop, (void (*)(decltype(vec_l) &))(Rshift),
            vec_l);

  return 0;
}

