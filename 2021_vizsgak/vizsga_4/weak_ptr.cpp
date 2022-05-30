#include <iostream>
#include <memory>
#include <variant>
#include <list>

std::list<std::variant<int, char>> unwrap(std::list<std::weak_ptr<std::variant<int, char>>> l) {
    std::list<std::variant<int, char>> tmp;
    for (auto& e : l) {
        tmp.push_back(*(e.lock()));
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& os, std::list<std::weak_ptr<std::variant<int, char>>> l) {
    std::list<std::variant<int, char>> tmp = unwrap(l);
    for (auto& e : tmp) {
        if (int* n = std::get_if<int>(&e)) {
            std::cout << *n << ' ';
        } else if (char* c = std::get_if<char>(&e)) {
            std::cout << *c << ' ';
        }
    }
    std::cout << std::endl;
    return os;
}

int main() {
    using VariantOfIntChar = std::variant<int, char>;
    VariantOfIntChar x1(4);
    VariantOfIntChar x2('a');

    auto sp1 = std::make_shared<VariantOfIntChar>(x1);
    auto sp2 = std::make_shared<VariantOfIntChar>(x2);

    using WeakPtrList = std::list<std::weak_ptr<VariantOfIntChar>>;
    WeakPtrList myll;
    myll.push_back(sp1);
    myll.push_back(sp2);

    {
    VariantOfIntChar x3(55);
    auto sp3 = std::make_shared<VariantOfIntChar>(x3);
    myll.push_back(sp3);
    std::cout << "linkedList before x3 is freed: " << myll << std::endl;
    }
    std::cout << "linkedList after x3 is freed: " << myll << std::endl;
}