#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#define FUNC_TIMER timer for_func_timer_object(__FUNCTION__);

class timer {
 private:
  std::chrono::system_clock::time_point start;
  std::chrono::system_clock::time_point end;
  bool flg;
  std::string str;

 public:
  timer() : flg(true) { start = end = std::chrono::system_clock::now(); }
  timer(std::string _str) : flg(true), str(_str) {
    start = end = std::chrono::system_clock::now();
  }

  ~timer() {
    stop();
    print(str);
  }

  void restart() {
    flg = true;
    start = std::chrono::system_clock::now();
  }
  void stop() {
    flg = false;
    end = std::chrono::system_clock::now();
  }
  void print() {
    if (flg) stop();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << "\n";
  }

  void print(const std::string &prefix_text) {
    if (flg) stop();
    std::cout << prefix_text << ":"
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                     .count()
              << "\n";
  }
};

template <class Func, class... Args>
void loop_time(const std::string tag, const size_t loop, Func *func,
               Args... args) {
  timer t(tag);

  for (size_t i = 0; i < loop; ++i) {
    func(args...);
  }
}

