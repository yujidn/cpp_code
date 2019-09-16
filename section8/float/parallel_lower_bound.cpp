#include <algorithm>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

#include "../../timer/timer_class.hpp"

// 10^8
const uint64_t vector_num = 1000 * 1000 * 100;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

int main() {
  timer t;
  for (uint64_t size = 100; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<float> vec;
    std::vector<float> vec_for_seq;
    std::vector<float> vec_for_par;
    std::vector<float> vec_for_par_unseq;

    vec.reserve(size);
    vec_for_seq.reserve(size);
    vec_for_par.reserve(size);
    vec_for_par_unseq.reserve(size);

    // 中身が同じ4つのvectorを作る
    // memcpyとかでもおｋ
    for (size_t s = 0; s < size; ++s) {
      vec.push_back(s);
      vec_for_seq.push_back(s);
      vec_for_par.push_back(s);
      vec_for_par_unseq.push_back(s);
    }

    std::vector<float> key(100);
    for (auto &k : key) {
      k = int_rand(engine) % size;
    }

    t.restart();
    for (const auto &k : key) {
      std::lower_bound(vec.begin(), vec.end(), k);
    }

    t.print("lower_bound");
    // 2分探索を並列化できるのかな？って思ってたら無いらしい
    // t.restart();

    // for (const auto &k : key) {
    //   std::lower_bound(std::execution::seq, vec_for_seq.begin(),
    //                    vec_for_seq.end(), k);
    // }

    // t.print("seq_lower_bound");
    // t.restart();

    // for (const auto &k : key) {
    //   std::lower_bound(std::execution::par, vec_for_par.begin(),
    //                    vec_for_par.end(), k);
    // }

    // t.print("par_lower_bound");
    // t.restart();

    // for (const auto &k : key) {
    //   std::lower_bound(std::execution::par_unseq, vec_for_par_unseq.begin(),
    //                    vec_for_par_unseq.end(), k);
    // }

    // t.print("par_unseq_lower_bound");
  }
  return 0;
}
