#include <chrono>
#include <string>
#include <iostream>

using namespace std;

class IntVector {
  int* firstElement;
  size_t capacity;
  size_t size;
public:
  IntVector() : capacity(10), size(0) {
    cout << "IntVector class constructor called\n";
    firstElement = new int[capacity];
  }
  IntVector& AddElement(int);
  int Print();
  IntVector(const IntVector&);
  IntVector& operator=(const IntVector&);
  IntVector(IntVector&& other) noexcept;
  IntVector& operator=(IntVector&& other) noexcept;
  ~IntVector();
};

IntVector::IntVector(const IntVector& other) : capacity(other.capacity), size(other.size) {
  cout << "Copy constructor called\n";
  firstElement = new int[capacity];
  for ( size_t s = 0; s<size; s++) {
    *(firstElement + s) = other.firstElement[s];
  }
}

IntVector& IntVector::operator=(const IntVector& other) {
  cout << "Copy assingment called\n";
  if (this == &other) return *this;
  delete[] firstElement;
  size = other.size;
  capacity = other.capacity;
  firstElement = new int[capacity];
  for ( size_t s = 0; s<size; s++) {
    *(firstElement + s) = other.firstElement[s];
  }
  return *this;
}

IntVector::IntVector(IntVector&& other) noexcept : capacity(other.capacity), size(other.size) { 
  cout << "move constructor called\n";
  firstElement = other.firstElement;
  other.firstElement = NULL;
}

IntVector& IntVector::operator=(IntVector&& other) noexcept {
  cout << "move assingment called\n";
  if (this == &other) return *this;
  delete[] firstElement;
  capacity = other.capacity;
  size = other.size;
  firstElement = other.firstElement;
  other.firstElement = NULL;
  return *this;
}

IntVector::~IntVector() {
  cout << "Destructor called.\n";
  delete[] firstElement;
}

IntVector& IntVector::AddElement(int n) {
  // increase size of vector
  if (capacity == size) {
    cout << "Allocating new memory.\n";
    int* newAddress = new int[capacity+10];
    for (int i = 0; i < capacity; i++) {
      newAddress[i] = firstElement[i];
    }
    delete[] firstElement;
    firstElement = newAddress;
    capacity += 10;
  } else {
    *(firstElement + size) = n;
  }
  size++;
  return *this;
}

int IntVector::Print() {
  if (size == 0) return 0;
  for (size_t s = 0; s<size; s++) {
    cout << firstElement[s] << "\t";
  }
  cout << "\n";
  return 1;
}

void swapIntVecs(IntVector& a, IntVector& b) {
  IntVector tmp{ move(b) };
  cout << "... temp created.\n";
  b = move(a);
  cout << "... b = a\n";
  a = move(tmp);
  cout << "... a = temp\n";
}

void test(int n) {
  IntVector iv;
  for ( int i = 0; i<n; i++) {
    iv.AddElement(i);
  }
  IntVector iv2(iv);
  iv2.Print();
  iv.AddElement(20);
  iv.Print();
  swapIntVecs(iv, iv2);
  iv.Print();
  iv2.Print();
}

int main() {
  test(20);
  return 0;
}
