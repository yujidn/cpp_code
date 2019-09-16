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
  uint64_t sum = 0;
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
      int r = int_rand(engine);
      vec.push_back(r);
      vec_for_seq.push_back(r);
      vec_for_par.push_back(r);
      vec_for_par_unseq.push_back(r);
    }

    t.restart();
    sum += *std::find(vec.begin(), vec.end(), 1);

    t.print("find");
    t.restart();

    sum += *std::find(std::execution::seq, vec_for_seq.begin(),
                      vec_for_seq.end(), 1);

    t.print("seq_find");
    t.restart();

    sum += *std::find(std::execution::par, vec_for_par.begin(),
                      vec_for_par.end(), 1);

    t.print("par_find");
    t.restart();

    sum += *std::find(std::execution::par_unseq, vec_for_par_unseq.begin(),
                      vec_for_par_unseq.end(), 1);

    t.print("par_unseq_find");
  }
  std::cout << sum << std::endl;
  return 0;
}
