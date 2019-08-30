#include <iostream>
#include <vector>

class ConstractShow {
 public:
  int val;
  ConstractShow(int v) {
    val = v;
    std::cout << val << ","
              << "Constract" << std::endl;
  }
  ~ConstractShow() {
    std::cout << val << ","
              << "Destract" << std::endl;
  }
  ConstractShow(const ConstractShow &show) : val(show.val) {
    std::cout << val << ","
              << "Copy" << std::endl;
  }
};

int main(void) {
  ConstractShow show(1);
  std::vector<ConstractShow> vec;

  std::cout << "push_back" << std::endl;
  vec.push_back(show);
  std::cout << "push_back with construct" << std::endl;
  vec.push_back(2);
  std::cout << "emplace_back with construct" << std::endl;
  vec.emplace_back(3);

  std::cout << "end test" << std::endl;
}
