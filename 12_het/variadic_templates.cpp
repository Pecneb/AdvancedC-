#include <iostream>

template<typename T>
double sum(T lastparam) {
  return lastparam;
}

template<typename T, typename... Params>
double sum(T firstparam, Params... p) {
  return firstparam + sum(p...);
}

int main() {
  std::cout << sum(1.5, 2.2, 3.7) << std::endl;
  std::string str = "Hey";
  decltype(str) t;
  std::cout << t << std::endl;
  return 0;
}
