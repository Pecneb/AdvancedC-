#include <iostream>
#include <functional>
#include <utility>

using namespace std;

/* Pretty much a self made bind2nd() function */
template < typename Function, typename SecondArgType >

class partial_apply_2nd {

private:

  Function function; /* function to execute */

  SecondArgType second; /* second arg of function */

public:

  partial_apply_2nd(Function f, SecondArgType s) : function(f), second(s) {} /* construct the object with a function, and the second argument of the function */

  /* functor operator -> call constructed object with the first arg of the function */
  template < typename FirstArgType >

  decltype( auto ) operator()( FirstArgType&& first ) {

    return function( forward< FirstArgType >( first ), second );
  
  }
};

class Operations_manager {

  private:
  
    int count = 0;

  public:
  
    int add( int a, int b ) {
    
      count++;
      
      cout << "Computing " << a << " + " << b << '\n';
      
      return a+b;
    
    }

    void printStatus() {

      cout << "Operations called: " << count << '\n';
    
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

  auto greaterThan10 = bind( greater<int>(), placeholders::_1, 10);

  cout << "15 is greater than 10? " << ( greaterThan10(15) ? "Yes" : "No" ) << '\n';

  auto thousandTimesSomething = bind( function< int( int, int ) >( [] ( int x, int m) -> int { return x*m; } ), placeholders::_1, 1000);

  cout << "This is 1000 x 1000 = " << thousandTimesSomething(1000) << '\n'; 
 
  Operations_manager opm;

  auto addTo3 = bind( &Operations_manager::add, placeholders::_1, placeholders::_2, 3 );

  cout << addTo3( opm, 5 ) << '\n';

  return 0;

}
