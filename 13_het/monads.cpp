#include <iostream>

int fibonacci(int number) {
  if (number < 3) return 1;
  return fibonacci(number-1) + fibonacci(number-2);
}

int main() {
  std::cout << "fibonacci(50) = " << fibonacci(50) << std::endl;
  return 0;
}
