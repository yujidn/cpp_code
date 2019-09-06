#include <iostream>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^6
const uint64_t vector_num = 1000 * 1000;
// 10^3
const size_t loop = 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 10);

class vector_class {
 private:
  std::vector<int> vec;

 public:
  void set_vec_by_value(std::vector<int> _vec) { vec = _vec; }
  void set_vec_by_reference(const std::vector<int> &_vec) { vec = _vec; }
  std::vector<int> get_vec_by_value() { return vec; }
  std::vector<int> &get_vec_by_reference() { return vec; }
  const std::vector<int> &get_vec_by_const_reference() const { return vec; }
};

void set_vec_by_value(vector_class &vec_class, std::vector<int> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    vec_class.set_vec_by_value(vec);
    vec[i] = i;
  }
}
void set_vec_by_reference(vector_class &vec_class, std::vector<int> &vec) {
  FUNC_TIMER;
  for (size_t i = 0; i < loop; ++i) {
    vec_class.set_vec_by_reference(vec);
    vec[i] = i;
  }
}
int get_vec_by_value(vector_class &vec_class) {
  FUNC_TIMER;
  int sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    auto vec = vec_class.get_vec_by_value();
    sum += vec[i];
  }
  return sum;
}
int get_vec_by_reference(vector_class &vec_class) {
  FUNC_TIMER;
  int sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    auto &vec = vec_class.get_vec_by_reference();
    vec[i] = i;
    sum += vec[i];
  }
  return sum;
}
int get_vec_by_const_reference(vector_class &vec_class) {
  FUNC_TIMER;
  int sum = 0;
  for (size_t i = 0; i < loop; ++i) {
    const auto &vec = vec_class.get_vec_by_const_reference();
    sum += vec[i];
  }
  return sum;
}
int main(void) {
  std::vector<int> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec[i] = int_rand(engine);
  }
  vector_class vec_class;

  set_vec_by_value(vec_class, vec);
  set_vec_by_reference(vec_class, vec);
  int sum = 0;
  sum += get_vec_by_value(vec_class);
  sum += get_vec_by_reference(vec_class);
  sum += get_vec_by_const_reference(vec_class);
  std::cout << sum << std::endl;

  return 0;
}

