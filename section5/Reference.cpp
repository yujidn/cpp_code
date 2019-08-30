#include <iostream>

class ConstractShow {
 public:
  int val;
  ConstractShow(int v) {
    val = v;
    std::cout << "Constract" << std::endl;
  }
  ~ConstractShow() { std::cout << "Destract" << std::endl; }
  ConstractShow(const ConstractShow &show) : val(show.val) {
    std::cout << "Copy" << std::endl;
  }
};

void CallByValue(ConstractShow show) {
  std::cout << __FUNCTION__ << std::endl;
  show.val += 1;
  std::cout << show.val << std::endl;
}

void ReferenceValue(ConstractShow &show) {
  std::cout << __FUNCTION__ << std::endl;
  show.val += 1;
  std::cout << show.val << std::endl;
}

void ConstReferenceValue(const ConstractShow &show) {
  std::cout << __FUNCTION__ << std::endl;
  // compile error!!
  // show.val += 1;
  std::cout << show.val << std::endl;
}

int main(void) {
  ConstractShow show(1);
  std::cout << "call start" << std::endl;
  CallByValue(show);
  ReferenceValue(show);
  ConstReferenceValue(show);
  std::cout << "call end" << std::endl;
}
