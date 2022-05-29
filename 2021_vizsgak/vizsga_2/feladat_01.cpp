#include <list>
#include <optional>
#include <variant>
#include <any>
#include <iostream>

std::optional<int> findLargestInt(const std::list< std::variant<int,double> >& numbers) {

    std::optional<int> retval;

    for ( auto n : numbers ) {
    
        try {

            int tmp = std::get< int >( n );

            if ( retval ) {
            
                if ( retval.value() < tmp ) retval = tmp;
            
            } else {
            
                retval = tmp;

            }

        } catch(const std::bad_variant_access& e ) {
          
            continue;
        
        }

    }

    return retval;

}

std::optional<int> findLargestInt(const std::list<std::any>& numbers) {

    std::optional<int> retval;

    for ( auto n : numbers ) {
    
        try {

            int tmp = std::any_cast< int >( n );

            if ( retval ) {
            
                if ( retval.value() < tmp ) retval = tmp;
            
            } else {
            
                retval = tmp;

            }

        } catch(const std::bad_any_cast& e ) {
          
            continue;
        
        }

    }

    return retval;

}

int main() {
    std::list<std::variant<int,double>> numbers = {1, 2, 3.14};
    std::optional<int> expected = 2;
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers.pop_front();
    expected = 2;
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers.pop_front();
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers = {0.5, 6.66};
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    std::list<std::any> things = {3.1416, -20, 10};
    expected = 10;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things.pop_back();
    expected = -20;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things = {-42, numbers, "something"};
    expected = -42;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things.pop_front();
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(things)) << std::endl;
}
