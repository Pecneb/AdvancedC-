#include <iostream>
#include <array>

constexpr int factorial(int n) {
    if (n < 2) return 1;
    return n * factorial(n - 1);
}

std::ostream& operator<<(std::ostream& os, std::array<int, factorial(2*1+1)> arr) {
    for (int& e : arr) std::cout << e << ' ';
    std::cout << std::endl;
    return os;
}

int main() {
    std::cout << "5! = " << factorial(5) << '\n';
    std::cout << "8! = " << factorial(8) << '\n';
    std::cout << "(3*3)! = " << factorial(3*3) << '\n';
    
    std::array<int, factorial(2*1+1)> arr;
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = factorial(i);
    }
    std::cout << "array contents: " << arr << '\n';
    
    return 0;
}