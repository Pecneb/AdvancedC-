#include <iostream>
#include <utility>
#include <functional>
#include <exception>

template<class Function, class Param>
void tryAndCatch(Function f, Param &&p) // ezt a sort modositsa, ahogy szukseges!
{
    // adja meg az implementaciot!
    try {
        f(std::forward<Param>(p));
    } catch( std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

int main() {
    auto printSquare = [](int n) { std::cout << n*n << '\n'; };
    auto oneOverX = [](double x) {
        if (x == 0.0) throw std::invalid_argument("Division by zero");
        std::cout << 1.0/x << '\n';
    };
    auto increment = [](int& n) { ++n; };
    tryAndCatch(printSquare, 4);
    tryAndCatch(oneOverX, 4);
    tryAndCatch(oneOverX, 0);

    int num = 2;
    tryAndCatch(increment, num);
    std::cout << "After increment: " << num << '\n';

    auto printAndClear = [](std::vector<int>&& v) {
        if (v.empty()) throw std::logic_error("Vector is empty");
        for (const auto& i : v) std::cout << i << '\n';
        v.clear();
    };
    std::vector<int> vec = {1, 2, 3};
    tryAndCatch(printAndClear, std::move(vec));
    tryAndCatch(printAndClear, std::move(vec));
    tryAndCatch(printAndClear, std::vector<int>{4, 3, 2, 1});

    tryAndCatch([](int x){std::cout << x/2 << '\n';}, 111);
}
