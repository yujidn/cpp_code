#include <iostream>

class constract_show {
 public:
  int val;

  constract_show(int v) {
    val = v;
    std::cout << "Constract" << std::endl;
  }
  ~constract_show() { std::cout << "Destract" << std::endl; }
  constract_show(const constract_show &show) : val(show.val) {
    std::cout << "Copy" << std::endl;
  }
};

constract_show show(1);

void call_by_value(constract_show show) {
  std::cout << __FUNCTION__ << std::endl;
  show.val += 1;
  std::cout << show.val << std::endl;
}

void reference_value(constract_show &show) {
  std::cout << __FUNCTION__ << std::endl;
  show.val += 1;
  std::cout << show.val << std::endl;
}

void const_reference_value(const constract_show &show) {
  std::cout << __FUNCTION__ << std::endl;
  // compile error!!
  // show.val += 1;
  std::cout << show.val << std::endl;
}

constract_show get_value() {
  std::cout << __FUNCTION__ << std::endl;
  return show;
}
constract_show &get_reference() {
  std::cout << __FUNCTION__ << std::endl;
  return show;
}

int main(void) {
  std::cout << "start" << std::endl;
  call_by_value(show);
  reference_value(show);
  const_reference_value(show);
  auto v1 = get_value();
  auto v2 = get_reference();
  auto &v3 = get_reference();
  std::cout << "end" << std::endl;
}
