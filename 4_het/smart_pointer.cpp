#include <iostream>
#include <string>

template <class T>
class SmartPtr {
  T *ptr; 
public:
  explicit SmartPtr(T *p = NULL) { ptr = p; }
  ~SmartPtr() { delete(ptr); }
  // SmartPtr(const SmartPtr<T> &other) = delete;
  // &SmartPtr<T> operator=(SmartPtr<T> &other) = delete;
  T & operator *() { 
    std::cout << *ptr << " destructed\n";
    return *ptr; 
  }
  T * operator ->() { return ptr; }
};

int main() {
  SmartPtr<int> intPtr(new int());
  *intPtr = 20;
  std::cout << *intPtr << std::endl;
  SmartPtr<std::string> strPtr(new std::string());
  *strPtr = "Yo man!";
  std::cout << *strPtr << std::endl;
  std::cout << strPtr->size() << std::endl; 
  return 0;
}
