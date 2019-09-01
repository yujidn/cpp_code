#include <iostream>
#include <thread>
#include "./timer_class.hpp"

void stop(int a, std::string b, float c) {
  std::cout << "stop" << a << " " << b << " " << c << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

int main() {
  timer t;
  FUNC_TIMER;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  t.print();
  t.restart();
  std::this_thread::sleep_for(std::chrono::seconds(2));

  loop_time("stop", 2, stop, 10, "b", 0.0);
  t.print("test");
  return 0;
}
