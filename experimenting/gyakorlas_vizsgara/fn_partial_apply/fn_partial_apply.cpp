#include <iostream>
#include <functional>
#include <utility>

using namespace std;

template < typename Function, typename SecondArgType >

class partial_apply_2nd {

private:
  
  Function function;

  SecondArgType second;

public:

  partial_apply_2nd(Function f, SecondArgType s) : function(f), second(s) {}

  template < typename FirstArgType >

  decltype( auto ) operator()( FirstArgType&& first ) {

    return function( forward< FirstArgType >( first ), second );
  
  }
};

int main() {

  partial_apply_2nd< function< int( int, int ) >, int > somethingPlus5( 
      []( int a, int b ) -> int { return a + b; }, 5 );

  cout << somethingPlus5( 2 ) << '\n';
  
  cout << somethingPlus5( 10 ) << '\n';

  return 0;

}
