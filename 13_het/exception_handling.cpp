#include <iostream>
#include <exception>
#include <cstring>
#include <stdlib.h>

class MyOwnAPIException : public std::exception {
  public:
  const char* what() const noexcept override {
    const char* e = "This should not happen";
    return e;
  }
};

double throw_exception(double a, double b) {
  if (b == 0) {
    throw MyOwnAPIException();
  }
  return a / b;
}

int main() {
  try {
    std::cout << "10 / 0 = " << throw_exception(10, 0) << std::endl;
  } catch (std::exception& e) {
    std::cout << "Exception " << e.what() << std::endl;
  }
  try {
    std::cout << "10 / 2 = " << throw_exception(10, 2) << std::endl;
  } catch(std::exception& e) {
    std::cout << "Exception " << e.what() << std::endl;
  }
  return 0;
}
