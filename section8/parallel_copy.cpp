#include <algorithm>
#include <execution>  // 現段階ではこのヘッダを追加する必要がある
#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^8
const uint64_t vector_num = 1000 * 1000 * 100;

std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, vector_num);

int main() {
  timer t;
  for (uint64_t size = 100; size <= vector_num; size *= 10) {
    std::cout << "---" << size << "--- " << std::endl;
    std::vector<int> vec;
    std::vector<int> vec_for_seq;
    std::vector<int> vec_for_par;
    std::vector<int> vec_for_par_unseq;

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

    // コピ―先
    std::vector<int> copy_vec(size);

    t.restart();
    std::copy(vec.begin(), vec.end(), copy_vec.begin());

    t.print("vector_copy");
    t.restart();

    std::copy(std::execution::seq, vec_for_seq.begin(), vec_for_seq.end(),
              copy_vec.begin());

    t.print("vector_seq_copy");
    t.restart();

    std::copy(std::execution::par, vec_for_par.begin(), vec_for_par.end(),
              copy_vec.begin());

    t.print("vector_par_copy");
    t.restart();

    std::copy(std::execution::par_unseq, vec_for_par_unseq.begin(),
              vec_for_par_unseq.end(), copy_vec.begin());

    t.print("vector_par_unseq_copy");
    t.restart();

    std::memcpy(&(copy_vec[0]), &(vec[0]), size * sizeof(int));

    t.print("memcpy");
  }
  return 0;
}
