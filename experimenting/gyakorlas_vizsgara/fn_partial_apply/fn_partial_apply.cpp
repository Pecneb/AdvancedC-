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

  partial_apply_2nd< function< bool( int, int ) >, int > greaterThan18( greater< int >(), 18 );

  cout << "19 is greater than 18? " << ( greaterThan18( 19 ) ? "Yes" : "No" ) << '\n';

  cout << "17 is greater than 18? " << ( greaterThan18( 17 ) ? "Yes" : "No" ) << '\n';

  return 0;

}
