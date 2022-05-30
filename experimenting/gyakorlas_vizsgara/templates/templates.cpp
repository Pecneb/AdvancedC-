#include <iostream>
#include <vector>

/* Test whether a type has iterator or not */
template<typename T>
class has_iter {
private:
    typedef char yes[1];
    typedef char no[2];

    template<typename C>
    static yes& test(typename C::iterator*);

    template<typename>
    static no& test(...);

public:
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
};

/* has_iter_w_type_traits */

#include <type_traits>

template<typename T, typename = void>
struct has_iter_w_type_traits : std::false_type {};

template<typename T>
struct has_iter_w_type_traits<T, std::void_t<typename T::iterator>> : std::true_type {};

int main() {
    std::cout << has_iter<std::vector<int>>::value << std::endl;
    std::cout << has_iter<int>::value << std::endl; 

    std::cout << has_iter_w_type_traits<std::vector<int>>::value << std::endl;
    std::cout << has_iter_w_type_traits<int>::value << std::endl;

    return 0;
}