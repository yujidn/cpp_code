#include <chrono>
#include <iostream>
#include <thread>

int main() {
  // タイマースタート
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "hello world!" << std::endl;

  // タイマーエンド
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

  // タイマー間の時間をns単位で取得
  std::cout << "[ns] : "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << std::endl;
  std::cout << "[us] : "
            << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                   .count()
            << std::endl;
  std::cout << "[ms] : "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << std::endl;
  std::cout
      << "[ s] : "
      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
      << std::endl;
  std::cout
      << "[ m] : "
      << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
      << std::endl;
  std::cout
      << "[ h] : "
      << std::chrono::duration_cast<std::chrono::hours>(end - start).count()
      << std::endl;
  return 0;
}
