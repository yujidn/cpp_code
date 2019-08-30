#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

#include "../timer/timer_class.hpp"

int main() {
  std::cout << "vector<int>    : " << sizeof(std::vector<int>) << std::endl;
  std::cout << "vector<double> : " << sizeof(std::vector<double>) << std::endl;
  std::cout << "list<int>      : " << sizeof(std::list<int>) << std::endl;
  std::cout << "list<double>   : " << sizeof(std::list<double>) << std::endl;
  std::cout << "deque<int>     : " << sizeof(std::deque<int>) << std::endl;
  std::cout << "deque<double>  : " << sizeof(std::deque<double>) << std::endl;
  std::cout << "map<int,int>         : " << sizeof(std::map<int, int>)
            << std::endl;
  std::cout << "map<double,double>   : " << sizeof(std::map<double, double>)
            << std::endl;

  std::cout << "unordered_map<int,int>       : "
            << sizeof(std::unordered_map<int, int>) << std::endl;
  std::cout << "unordered_map<double,double> : "
            << sizeof(std::unordered_map<double, double>) << std::endl;
  return 0;
}
