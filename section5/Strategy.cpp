#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "../timer/timer_class.hpp"

// 10^3
const uint64_t vector_num = 1000;
// 10^6
const size_t loop = 1000 * 1000;
std::random_device seed_gen;
auto engine = std::mt19937_64(seed_gen());
auto int_rand = std::uniform_int_distribution<>(0, 5);

class Base {
 protected:
  int val;

 public:
  Base() { val = int_rand(engine); }
  virtual const int& Val() = 0;
};

class E0 : public Base {
 public:
  const int& Val() {
    val += 0;
    return val;
  }
};
class E1 : public Base {
 public:
  const int& Val() {
    val += 1;
    return val;
  }
};
class E2 : public Base {
 public:
  const int& Val() {
    val += 2;
    return val;
  }
};
class E3 : public Base {
 public:
  const int& Val() {
    val += 3;
    return val;
  }
};
class E4 : public Base {
 public:
  const int& Val() {
    val += 4;
    return val;
  }
};
class E5 : public Base {
 public:
  const int& Val() {
    val += 5;
    return val;
  }
};

int main(void) {
  std::vector<int> vec(vector_num);
  for (size_t i = 0; i < vector_num; ++i) {
    vec[i] = int_rand(engine);
  }

  Base* base = nullptr;
  E0 e0;
  E1 e1;
  E2 e2;
  E3 e3;
  E4 e4;
  E5 e5;
  int64_t sum = 0;
  std::map<int, Base*> map;
  map.insert(std::make_pair(0, &e0));
  map.insert(std::make_pair(1, &e1));
  map.insert(std::make_pair(2, &e2));
  map.insert(std::make_pair(3, &e3));
  map.insert(std::make_pair(4, &e4));
  map.insert(std::make_pair(5, &e5));

  std::vector<Base*> extendVec;
  extendVec.push_back(&e0);
  extendVec.push_back(&e1);
  extendVec.push_back(&e2);
  extendVec.push_back(&e3);
  extendVec.push_back(&e4);
  extendVec.push_back(&e5);

  BLOCK_TIMER;
  BLOCK_START;
  for (size_t i = 0; i < loop; ++i) {
    for (auto& v : vec) {
      switch (v) {
        case 0:
          base = &e0;
          break;
        case 1:
          base = &e1;
          break;
        case 2:
          base = &e2;
          break;
        case 3:
          base = &e3;
          break;
        case 4:
          base = &e4;
          break;
        case 5:
          base = &e5;
          break;
      }
      sum += base->Val();
    }
  }
  BLOCK_CHECK;
  for (size_t i = 0; i < loop; ++i) {
    for (auto& v : vec) {
      base = map.at(v);
      sum += base->Val();
    }
  }

  BLOCK_CHECK;
  for (size_t i = 0; i < loop; ++i) {
    for (auto& v : vec) {
      base = extendVec[v];
      sum += base->Val();
    }
  }
  BLOCK_CHECK;

  std::cout << sum << std::endl;
}

